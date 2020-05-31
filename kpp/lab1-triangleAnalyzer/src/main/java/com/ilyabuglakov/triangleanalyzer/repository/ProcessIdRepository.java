package com.ilyabuglakov.triangleanalyzer.repository;

import com.ilyabuglakov.triangleanalyzer.entity.ProcessIdEntity;
import org.springframework.data.repository.CrudRepository;

public interface ProcessIdRepository extends CrudRepository<ProcessIdEntity, Long> {
    boolean existsByProcessId(Long processId);
    ProcessIdEntity findByProcessId(Long processId);
}
