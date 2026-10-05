# Тулчейн для сборки i386-.so под боевой контейнер (Ubuntu 22.04, glibc 2.35).
# Собирается один раз, кэшируется. Общий для загрузчика и плагинов (имя pwse-toolchain).
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
        gcc \
        gcc-multilib \
        make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
