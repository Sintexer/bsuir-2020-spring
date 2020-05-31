package com.ilyabuglakov.triangleanalyzer.repository;

import com.ilyabuglakov.triangleanalyzer.entity.TriangleEntity;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface TriangleRepository extends CrudRepository<TriangleEntity, Long> {
    List<TriangleEntity> findAllByProcessId(long processId);
    boolean existsBySide1AndSide2AndSide3(int side1, int side2, int side3);
    TriangleEntity findBySide1AndSide2AndSide3(int side1, int side2, int side3);
}
