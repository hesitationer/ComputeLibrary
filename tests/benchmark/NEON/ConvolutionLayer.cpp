/*
 * Copyright (c) 2017 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "arm_compute/core/TensorShape.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/NEON/functions/NEConvolutionLayer.h"
#include "arm_compute/runtime/Tensor.h"
#include "arm_compute/runtime/TensorAllocator.h"
#include "tests/NEON/Accessor.h"
#include "tests/benchmark/fixtures/ConvolutionLayerFixture.h"
#include "tests/datasets/system_tests/alexnet/AlexNetConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/googlenet/inceptionv1/GoogLeNetInceptionV1ConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/googlenet/inceptionv4/GoogLeNetInceptionV4ConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/lenet5/LeNet5ConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/squeezenet/SqueezeNetConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/vgg/vgg16/VGG16ConvolutionLayerDataset.h"
#include "tests/datasets/system_tests/yolo/v2/YOLOV2ConvolutionLayerDataset.h"
#include "tests/framework/Macros.h"
#include "tests/framework/datasets/Datasets.h"
#include "utils/TypePrinter.h"

namespace arm_compute
{
namespace test
{
namespace
{
#ifdef ARM_COMPUTE_ENABLE_FP16
const auto data_types = framework::dataset::make("DataType", { DataType::F16, DataType::F32, DataType::QS8, DataType::QS16 });
#else  /* ARM_COMPUTE_ENABLE_FP16 */
const auto data_types = framework::dataset::make("DataType", { DataType::F32, DataType::QS8, DataType::QS16 });
#endif /* ARM_COMPUTE_ENABLE_FP16 */
} // namespace

using NEConvolutionLayerFixture = ConvolutionLayerFixture<Tensor, NEConvolutionLayer, Accessor>;

TEST_SUITE(NEON)

REGISTER_FIXTURE_DATA_TEST_CASE(AlexNetConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::ALL,
                                framework::dataset::combine(framework::dataset::combine(datasets::AlexNetConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", 1)));

REGISTER_FIXTURE_DATA_TEST_CASE(LeNet5ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::ALL,
                                framework::dataset::combine(framework::dataset::combine(datasets::LeNet5ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", 1)));

REGISTER_FIXTURE_DATA_TEST_CASE(GoogLeNetInceptionV1ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::ALL,
                                framework::dataset::combine(framework::dataset::combine(datasets::GoogLeNetInceptionV1ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", 1)));

REGISTER_FIXTURE_DATA_TEST_CASE(GoogLeNetInceptionV4ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::ALL,
                                framework::dataset::combine(framework::dataset::combine(datasets::GoogLeNetInceptionV4ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", 1)));

REGISTER_FIXTURE_DATA_TEST_CASE(SqueezeNetConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::ALL,
                                framework::dataset::combine(framework::dataset::combine(datasets::SqueezeNetConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", 1)));

TEST_SUITE(NIGHTLY)
REGISTER_FIXTURE_DATA_TEST_CASE(AlexNetConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::AlexNetConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 4, 8 })));

REGISTER_FIXTURE_DATA_TEST_CASE(LeNet5ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::LeNet5ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 4, 8 })));

REGISTER_FIXTURE_DATA_TEST_CASE(GoogLeNetInceptionV1ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::GoogLeNetInceptionV1ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 4, 8 })));

REGISTER_FIXTURE_DATA_TEST_CASE(GoogLeNetInceptionV4ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::GoogLeNetInceptionV4ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 4, 8 })));

REGISTER_FIXTURE_DATA_TEST_CASE(SqueezeNetConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::SqueezeNetConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 4, 8 })));

// 8 batches use about 2GB of memory which is too much for most devices!
REGISTER_FIXTURE_DATA_TEST_CASE(VGG16ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::VGG16ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 1, 4 })));

REGISTER_FIXTURE_DATA_TEST_CASE(YOLOV2ConvolutionLayer, NEConvolutionLayerFixture, framework::DatasetMode::NIGHTLY,
                                framework::dataset::combine(framework::dataset::combine(datasets::YOLOV2ConvolutionLayerDataset(), data_types),
                                                            framework::dataset::make("Batches", { 1, 4, 8 })));

TEST_SUITE_END()
TEST_SUITE_END()
} // namespace test
} // namespace arm_compute
