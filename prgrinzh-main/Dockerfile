FROM gcc:13
WORKDIR /app
RUN apt update && apt install -y cmake make libpoco-dev libssl-dev
COPY . .
RUN cmake -S. -Bbuild && cmake --build build --config Release
CMD ["./build/user_service"]