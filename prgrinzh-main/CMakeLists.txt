cmake_minimum_required(VERSION 3.10)
project(UserService)

set(CMAKE_CXX_STANDARD 17)

# === POCO ===
set(POCO_ROOT "C:/Users/kishki/poco")
set(POCO_LIB "${POCO_ROOT}/build/lib")
include_directories(${POCO_ROOT})                        # корневой include
include_directories(${POCO_ROOT}/Foundation/include)
include_directories(${POCO_ROOT}/Util/include)
include_directories(${POCO_ROOT}/Net/include)
include_directories(${POCO_ROOT}/JSON/include)
include_directories(${POCO_ROOT}/Crypto/include)
link_directories(${POCO_LIB})

# === Пути к OpenSSL (ты установил сюда) ===
set(OPENSSL_ROOT "C:/OpenSSL-Win64")
set(OPENSSL_INCLUDE "${OPENSSL_ROOT}/include")
set(OPENSSL_LIB "${OPENSSL_ROOT}/lib/VC/x64/MD")


# === Пути к jwt-cpp (скачай и положи в external/jwt-cpp) ===
set(JWT_INCLUDE "${CMAKE_SOURCE_DIR}/external/jwt-cpp/include")

# === Подключаем заголовочные файлы ===
include_directories(${POCO_INCLUDE})
include_directories(${OPENSSL_INCLUDE})
include_directories(${JWT_INCLUDE})

# === Указываем, где искать .lib-файлы ===
link_directories(${POCO_LIB})
link_directories(${OPENSSL_LIB})

# === Добавляем исполняемый файл ===
add_executable(user_service
    main.cpp
    UserService.cpp
    UserService.h
    AuthService.cpp
    AuthService.h
    UserStore.cpp
    UserStore.h
)

# === Линкуем библиотеки ===
target_link_libraries(user_service
    PocoFoundation
    PocoUtil
    PocoNet
    PocoJSON
    PocoCrypto
    ssl
    crypto
)
