package com.ilyabuglakov.triangleanalyzer.repository;

import com.ilyabuglakov.triangleanalyzer.entity.TriangleAttributesEntity;
import org.springframework.data.repository.CrudRepository;
import java.util.List;

public interface TriangleAttributesRepository extends CrudRepository<TriangleAttributesEntity, Long> {
    List<TriangleAttributesEntity> findAllByProcessId(Long processId);
}
