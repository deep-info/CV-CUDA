/*
 * SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file ColorTwist.hpp
 *
 * @brief Defines the private C++ Class for the ColorTwist operation.
 */

#ifndef CVCUDA_PRIV__COLOR_TWIST_HPP
#define CVCUDA_PRIV__COLOR_TWIST_HPP
#include "IOperator.hpp"

#include <cuda_runtime.h>
#include <cvcuda/OpColorTwist.h>
#include <nvcv/ImageBatch.hpp>
#include <nvcv/Tensor.hpp>

namespace cvcuda::priv {

class ColorTwist final : public IOperator
{
public:
    explicit ColorTwist();

    void operator()(cudaStream_t stream, const nvcv::Tensor &src, const nvcv::Tensor &dst,
                    const nvcv::Tensor &twist) const;

    void operator()(cudaStream_t stream, const nvcv::ImageBatchVarShape &src, const nvcv::ImageBatchVarShape &dst,
                    const nvcv::Tensor &twist) const;
};

} // namespace cvcuda::priv

#endif // CVCUDA_PRIV__COLOR_TWIST_HPP
