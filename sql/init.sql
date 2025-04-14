-- sql/init.sql

CREATE DATABASE IF NOT EXISTS metadb;

USE metadb;

CREATE TABLE IF NOT EXISTS file_metadata (
    id VARCHAR(36) PRIMARY KEY,
    filename VARCHAR(255) NOT NULL,
    filepath VARCHAR(255) NOT NULL,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    size BIGINT,
    node_ip VARCHAR(64),
    node_port INT
);
