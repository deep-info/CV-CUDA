/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2023   NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef NVCV_TENSORDATA_HPP
#define NVCV_TENSORDATA_HPP

#include "Optional.hpp"
#include "TensorData.h"
#include "TensorShape.hpp"

#include <nvcv/DataType.hpp>

namespace nvcv {

// Interface hierarchy of tensor contents
class TensorData
{
public:
    TensorData(const NVCVTensorData &data);

    int                         rank() const;
    const TensorShape          &shape() const &;
    const TensorShape::DimType &shape(int d) const &;
    const TensorLayout         &layout() const &;

    TensorShape shape() &&
    {
        return this->shape();
    }

    TensorShape::DimType shape(int d) &&
    {
        return this->shape(d);
    }

    TensorLayout layout() &&
    {
        return this->layout();
    }

    DataType dtype() const;

    const NVCVTensorData &cdata() const &;

    NVCVTensorData cdata() &&
    {
        return this->cdata();
    }

    static bool IsCompatibleKind(NVCVTensorBufferType kind)
    {
        return kind != NVCV_TENSOR_BUFFER_NONE;
    }

    template<typename DerivedTensorData>
    Optional<DerivedTensorData> cast() const;

    template<typename Derived>
    bool IsCompatible() const;

protected:
    TensorData() = default;

    NVCVTensorData &data() &;

private:
    NVCVTensorData                m_data{};
    mutable Optional<TensorShape> m_cacheShape;
};

class TensorDataStrided : public TensorData
{
public:
    Byte          *basePtr() const;
    const int64_t &stride(int d) const;

    static bool IsCompatibleKind(NVCVTensorBufferType kind)
    {
        return kind == NVCV_TENSOR_BUFFER_STRIDED_CUDA;
    }

protected:
    using TensorData::TensorData;
};

class TensorDataStridedCuda : public TensorDataStrided
{
public:
    using Buffer = NVCVTensorBufferStrided;

    TensorDataStridedCuda(const NVCVTensorData &data);
    TensorDataStridedCuda(const TensorShape &tshape, const DataType &dtype, const Buffer &buffer);

    static bool IsCompatibleKind(NVCVTensorBufferType kind)
    {
        return kind == NVCV_TENSOR_BUFFER_STRIDED_CUDA;
    }
};

} // namespace nvcv

#include "detail/TensorDataImpl.hpp"

#endif // NVCV_TENSORDATA_HPP
