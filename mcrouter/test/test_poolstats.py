#!/usr/bin/env python3
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

# pyre-unsafe

import os

import time

from mcrouter.test.MCProcess import Mcrouter
from mcrouter.test.McrouterTestCase import McrouterTestCase
from mcrouter.test.mock_servers import SleepServer


class TestPoolStats(McrouterTestCase):
    config = "./mcrouter/test/test_poolstats.json"
    null_route_config = "./mcrouter/test/test_nullroute.json"
    mcrouter_server_extra_args = []
    extra_args = [
        "--pool-stats-config-file=./mcrouter/test/test_poolstats_config.json",
        "--timeouts-until-tko=50",
        "--num-proxies=4",
    ]
    stat_prefix = "libmcrouter.mcrouter.0."
    pool_prefix = stat_prefix + "twmemcache.CI."
    count = 20
    durationMap = {}

    def setUp(self):
        self.mc = []
        for _i in range(3):
            self.mc.append(
                Mcrouter(
                    self.null_route_config, extra_args=self.mcrouter_server_extra_args
                )
            )
            self.add_server(self.mc[_i])

        # configure SleepServer for the east and wc pools
        for _i in range(3):
            self.mc.append(SleepServer())
            self.add_server(self.mc[_i + 3])

        self.mcrouter = self.add_mcrouter(self.config, extra_args=self.extra_args)

    def verify_stat(self, line, statname, expected, op):
        if self.pool_prefix + statname in line:
            s = line.split(":")[1].split(",")[0]
            if "GR" in op:
                self.assertGreater(int(s), expected)
                self.durationMap[statname] = int(s)
            elif "EQ" in op:
                self.assertEqual(int(s), expected)
            else:
                self.assertTrue(False)

    def check_pool_stats(self, stats_dir):
        file_stat = os.path.join(stats_dir, self.stat_prefix + "stats")
        verifiedStats = 0
        with open(file_stat) as f:
            for line in f.readlines():
                # Expect all east requests to fail because it
                # is running SleepServer

                if self.pool_prefix + "east" in line:
                    self.verify_stat(line, "east.requests.sum", self.count, "EQ")
                    self.verify_stat(
                        line, "east.final_result_error.sum", self.count, "EQ"
                    )
                    self.verify_stat(line, "east.connections", 1, "EQ")
                    self.verify_stat(line, "east.duration_us.avg", 0, "GR")
                    self.verify_stat(line, "east.total_duration_us.avg", 0, "GR")
                    verifiedStats += 1

                if self.pool_prefix + "west" in line:
                    self.verify_stat(line, "west.requests.sum", 2 * self.count, "EQ")
                    self.verify_stat(line, "west.connections", 2, "EQ")
                    self.verify_stat(line, "west.final_result_error.sum", 0, "EQ")
                    self.verify_stat(line, "west.duration_us.avg", 0, "GR")
                    self.verify_stat(line, "west.total_duration_us.avg", 0, "GR")
                    verifiedStats += 1

                if self.pool_prefix + "north" in line:
                    self.verify_stat(line, "north.requests.sum", self.count, "EQ")
                    self.verify_stat(line, "north.connections", 1, "EQ")
                    self.verify_stat(line, "north.final_result_error.sum", 0, "EQ")
                    self.verify_stat(line, "north.duration_us.avg", 0, "GR")
                    self.verify_stat(line, "north.total_duration_us.avg", 0, "EQ")
                    verifiedStats += 1

                if self.pool_prefix + "south" in line:
                    self.verify_stat(line, "south.requests.sum", self.count, "EQ")
                    self.verify_stat(line, "south.connections", 1, "EQ")
                    self.verify_stat(line, "south.final_result_error.sum", 0, "EQ")
                    self.verify_stat(line, "south.duration_us.avg", 0, "GR")
                    self.verify_stat(line, "south.total_duration_us.avg", 0, "GR")
                    verifiedStats += 1

        # These checks must be done outside the for loop
        self.assertTrue(
            self.durationMap["east.total_duration_us.avg"]
            >= self.durationMap["east.duration_us.avg"]
        )
        self.assertTrue(
            self.durationMap["west.total_duration_us.avg"]
            >= self.durationMap["west.duration_us.avg"]
        )
        self.assertTrue(
            self.durationMap["south.total_duration_us.avg"]
            >= self.durationMap["south.duration_us.avg"]
        )
        # for 'north' pool total_duration would be 0 and duration
        # would be greater than 0. so, the check is already done.
        self.assertTrue(verifiedStats == 20)

    def test_poolstats(self):
        n = 4 * self.count
        for i in range(0, n):
            m = i % 4
            if m == 0:
                key = f"twmemcache.CI.west:{i}:|#|id=123"
            elif m == 1:
                key = f"twmemcache.CI.west.1:{i}:|#|id=123"
            elif m == 2:
                key = f"twmemcache.CI.north:{i}:|#|id=123"
            else:
                key = f"twmemcache.CI.east:{i}:|#|id=123"
            self.mcrouter.get(key)
        self.assertGreater(int(self.mcrouter.stats()["cmd_get_count"]), 0)
        time.sleep(11)
        self.check_pool_stats(self.mcrouter.stats_dir)
