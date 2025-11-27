FROM archlinux:latest as base
RUN pacman -Sy
RUN pacman --noconfirm -S cmake make gcc openssl postgresql-libs

FROM base AS build
WORKDIR /app
COPY ./reservation .
RUN ./build.sh

FROM base AS release
WORKDIR /app
COPY --from=build /app/bin ./bin
COPY --from=build /app/libs ./libs
