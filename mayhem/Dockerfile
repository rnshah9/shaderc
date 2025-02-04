# Copyright 2016 The Shaderc Authors. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM ubuntu:22.04 as builder

RUN apt-get update

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential git cmake ninja-build python-is-python3 clang

WORKDIR /root
COPY . shaderc
RUN rm ~/shaderc/mayhem/fuzz_string_piece.cpp

WORKDIR shaderc
RUN ./utils/git-sync-deps

WORKDIR build
RUN cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/install \
    .. \
  && ninja install
COPY ./mayhem/fuzz_string_piece.cpp /root/shaderc/mayhem/
RUN clang++ ~/shaderc/mayhem/fuzz_string_piece.cpp -fsanitize=fuzzer,address -I ~/shaderc/libshaderc_util/include/libshaderc_util/ -o /fuzz


FROM ubuntu:22.04 as package
COPY --from=builder /install /install
COPY --from=builder /fuzz /fuzz_string_piece
