-- sql/init.sql

CREATE DATABASE IF NOT EXISTS metadb;

USE metadb;

CREATE TABLE IF NOT EXISTS file_metadata (
    id VARCHAR(36) PRIMARY KEY,
    filename VARCHAR(255) NOT NULL,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    size BIGINT,
    checksum VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS file_replicas (
    file_id VARCHAR(36),
    node_ip VARCHAR(64),
    node_port INT,
    filepath VARCHAR(255) NOT NULL,
    PRIMARY KEY(file_id, node_ip, node_port),
    FOREIGN KEY(file_id) REFERENCES file_metadata(id)
);
