-- Создание схемы chat
CREATE SCHEMA IF NOT EXISTS chat;

-- Таблица пользователей (User)
CREATE TABLE IF NOT EXISTS chat.users
(
    id BIGSERIAL PRIMARY KEY, -- Уникальный идентификатор пользователя
    username VARCHAR(50) NOT NULL UNIQUE, -- Логин пользователя
    password VARCHAR(255) NOT NULL -- Пароль пользователя
);

-- Таблица комнат чата (Chatroom)
CREATE TABLE IF NOT EXISTS chat.chatroom
(
    id BIGSERIAL PRIMARY KEY, -- Уникальный идентификатор комнаты
    name VARCHAR(50) NOT NULL, -- Название комнаты
    owner BIGINT NOT NULL, -- Владелец комнаты (ссылка на пользователя)
    password VARCHAR(100), -- Пароль для входа в комнату
    CONSTRAINT fk_owner FOREIGN KEY (owner) REFERENCES chat.users(id) -- Внешний ключ на таблицу пользователей
);

-- Таблица сообщений (Message)
CREATE TABLE IF NOT EXISTS chat.messages
(
    id BIGSERIAL PRIMARY KEY, -- Уникальный идентификатор сообщения
    sender VARCHAR(255), -- Автор сообщения (ссылка на пользователя)
    text text NOT NULL, -- Текст сообщения
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL, -- Дата и время отправки сообщения
    chatid BIGINT NOT NULL, -- Комната, в которой отправлено сообщение
    CONSTRAINT fk_room FOREIGN KEY (chatid) REFERENCES chat.chatroom(id) ON DELETE CASCADE -- Внешний ключ на таблицу комнат чата
);

-- Добавление индексов для ускорения работы с внешними ключами
CREATE INDEX IF NOT EXISTS idx_messages_sender ON chat.messages(sender);
CREATE INDEX IF NOT EXISTS idx_messages_chatid ON chat.messages(chatid);
CREATE INDEX IF NOT EXISTS idx_chatroom_owner ON chat.chatroom(owner);