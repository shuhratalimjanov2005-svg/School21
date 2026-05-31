resource "local_file" "my_creation" {
    content  = "я создаю свою первую инфраструктуру!"
    filename = "my_creation.txt"
}
# Создаем структуру папок для нашего будущего " проекта"
resource "local_file" "readme" {
    content  = "Архитектура : Статус - вечная стройка, приоритет - идеализация и мощь."
    filename = "project/README.md"
}

resource "local_file" "config" {
    content  = "scale = 'monumental'\nstatus = 'active_rebuild'"
    filename = "project/config.conf"
}

# 1. Создаем виртуальную сеть, чтобы наши контейнеры общались между собой
resource "docker_network" "private_network" {
  name = "divine_network"
}

# 2. Создаем базовый контейнер для нашей инфраструктуры
resource "docker_container" "bot_engine" {
  image = "ubuntu:latest"
  name  = "bot_engine_base"
  tty   = true  # Это заставит контейнер оставаться активным!
  networks_advanced {
    name = docker_network.private_network.name
  }
}
