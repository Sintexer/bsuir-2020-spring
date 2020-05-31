package com.ilyabuglakov.triangleanalyzer.repository;

import com.ilyabuglakov.triangleanalyzer.entity.StatisticEntity;
import org.springframework.data.repository.CrudRepository;

public interface StatisticRepository extends CrudRepository<StatisticEntity, Long> {
    StatisticEntity findByProcessId(Long processId);
}
