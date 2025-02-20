package edu.school21.sockets.repositories;

import java.util.Optional;

public interface CrudRepository<T> {
    void save(T entity);
    Optional<T> findById(Long id);
    void update(T entity);
    void delete(Long id);
    Iterable<T> findAll();
}