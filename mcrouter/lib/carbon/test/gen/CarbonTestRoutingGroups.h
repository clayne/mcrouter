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

#include <mcrouter/lib/carbon/RoutingGroups.h>

#include "mcrouter/lib/carbon/test/gen/CarbonTestMessages.h"

namespace carbon {

// ArithmeticLike
template <>
struct ArithmeticLike<carbon::test::TestRequest> {
  static const bool value = false;
};

template <>
struct ArithmeticLike<carbon::test::TestRequestStringKey> {
  static const bool value = false;
};

// DeleteLike
template <>
struct DeleteLike<carbon::test::TestRequest> {
  static const bool value = false;
};

template <>
struct DeleteLike<carbon::test::TestRequestStringKey> {
  static const bool value = false;
};

// GetLike
template <>
struct GetLike<carbon::test::TestRequest> {
  static const bool value = false;
};

template <>
struct GetLike<carbon::test::TestRequestStringKey> {
  static const bool value = false;
};

// UpdateLike
template <>
struct UpdateLike<carbon::test::TestRequest> {
  static const bool value = false;
};

template <>
struct UpdateLike<carbon::test::TestRequestStringKey> {
  static const bool value = false;
};
} // namespace carbon
