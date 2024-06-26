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
#pragma once

#include "mcrouter/lib/carbon/test/gen/gen-cpp2/CarbonThriftTest_types.h"
#include "mcrouter/lib/carbon/test/gen/gen-cpp2/CarbonThriftTest.h"

namespace carbon {
namespace test {

template <class ServerOnRequest>
class CarbonThriftTestServerOnRequestThrift : public thrift::CarbonThriftTestSvIf {
 public:
  CarbonThriftTestServerOnRequestThrift(
      std::unordered_map<
          folly::EventBase*,
          std::shared_ptr<ServerOnRequest>> serverOnRequestMap)
      : serverOnRequestMap_(std::move(serverOnRequestMap)) {}
  void async_tm_customRequest(
      apache::thrift::HandlerCallbackPtr<carbon::test::CustomReply> callback,
      const class carbon::test::CustomRequest& request) override final {
    onRequestThriftHelper<std::remove_reference_t<decltype(request)>>(
        request, std::move(callback));
  }
  void async_tm_thrift_test(
      apache::thrift::HandlerCallbackPtr<carbon::test::DummyThriftReply> callback,
      const class carbon::test::DummyThriftRequest& request) override final {
    onRequestThriftHelper<std::remove_reference_t<decltype(request)>>(
        request, std::move(callback));
  }
  void async_tm_test(
      apache::thrift::HandlerCallbackPtr<carbon::test::ThriftTestReply> callback,
      const class carbon::test::ThriftTestRequest& request) override final {
    onRequestThriftHelper<std::remove_reference_t<decltype(request)>>(
        request, std::move(callback));
  }
  void async_tm_mcVersion(
      apache::thrift::HandlerCallbackPtr<facebook::memcache::McVersionReply> callback,
      const class facebook::memcache::McVersionRequest& request) override final {
    onRequestThriftHelper<std::remove_reference_t<decltype(request)>>(
        request, std::move(callback));
  }
 // Return this factory instead of CarbonThriftTestAsyncProcessor from getProcessor(),
 // so that we don't use the default statically registered handlers
 class CarbonThriftTestAsyncProcessorCustomHandlers
     : public thrift::CarbonThriftTestAsyncProcessor {
  public:
   explicit CarbonThriftTestAsyncProcessorCustomHandlers(thrift::CarbonThriftTestSvIf* svif)
        : CarbonThriftTestAsyncProcessor(svif) {
     clearEventHandlers();
   }
 };
 std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor()
     override final {
   return std::make_unique<CarbonThriftTestAsyncProcessorCustomHandlers>(this);
 }

 private:
  std::unordered_map<
     folly::EventBase*,
     std::shared_ptr<ServerOnRequest>>
     serverOnRequestMap_;
  static thread_local ServerOnRequest* serverOnRequest_;

  template <class Request>
   void onRequestThriftHelper(
       const Request& request,
       apache::thrift::HandlerCallbackPtr<typename Request::reply_type>
           callback) {
     getServerOnRequest(callback->getEventBase())
         ->onRequestThrift(
             std::move(callback),
             std::move(const_cast<std::remove_const_t<Request>&>(request)));
   }

 // Returns the ServerOnRequest* associated with this evb
  ServerOnRequest* getServerOnRequest(folly::EventBase* evb) {
    if (serverOnRequest_ == nullptr) {
      auto it = serverOnRequestMap_.find(evb);
      CHECK(it != serverOnRequestMap_.end());
      serverOnRequest_ = it->second.get();
    }
    return serverOnRequest_;
  }
};

template <class ServerOnRequest>
thread_local ServerOnRequest*
    CarbonThriftTestServerOnRequestThrift<ServerOnRequest>::serverOnRequest_{nullptr};

} // namespace test
} // namespace carbon