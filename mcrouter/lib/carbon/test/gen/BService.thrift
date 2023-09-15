/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */
include "thrift/annotation/cpp.thrift"
include "mcrouter/lib/network/gen/Common.thrift"
include "mcrouter/lib/carbon/test/gen/B.thrift"

include "common/fb303/if/fb303.thrift"

cpp_include "mcrouter/lib/carbon/test/gen/BMessages.h"

namespace cpp2 carbon.test.B.thrift
namespace py3 carbon.test.B.thrift

service B extends fb303.FacebookService {
  B_TestBReply testB(1: B_TestBRequest request) (thread = "eb")
  Common_McVersionReply mcVersion(1: Common_McVersionRequest request) (thread = "eb")
}

@cpp.Type{name = "carbon::test::B::TestBReply"}
typedef B.TestBReply B_TestBReply
@cpp.Type{name = "carbon::test::B::TestBRequest"}
typedef B.TestBRequest B_TestBRequest
@cpp.Type{name = "facebook::memcache::McVersionReply"}
typedef Common.McVersionReply Common_McVersionReply
@cpp.Type{name = "facebook::memcache::McVersionRequest"}
typedef Common.McVersionRequest Common_McVersionRequest