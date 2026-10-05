# Тулчейн для сборки i386-плагина под боевой контейнер (Ubuntu 22.04, glibc 2.35).
# Образ общий с загрузчиком (имя pwse-toolchain), собирается один раз, кэшируется.
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
        gcc \
        gcc-multilib \
        make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
