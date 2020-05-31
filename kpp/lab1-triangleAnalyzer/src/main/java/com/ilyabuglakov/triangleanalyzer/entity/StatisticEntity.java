package com.ilyabuglakov.triangleanalyzer.entity;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(schema = "triangle_analyzer", name = "statistic")
public class StatisticEntity {

    @Id
    @GeneratedValue
    private long id;

    private long processId;
    private long totalRequestsCount;
    private long uniqueRequestCount;
    private long invalidRequestCount;

    public StatisticEntity() {}

    public StatisticEntity(Long processId, long totalRequestsCount, long uniqueRequestCount, long invalidRequestCount){
        this.processId = processId;
        this.totalRequestsCount = totalRequestsCount;
        this.uniqueRequestCount = uniqueRequestCount;
        this.invalidRequestCount = invalidRequestCount;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public long getProcessId() {
        return processId;
    }

    public void setProcessId(long process_id) {
        this.processId = process_id;
    }

    public long getTotalRequestsCount() {
        return totalRequestsCount;
    }

    public void setTotalRequestsCount(long totalRequestsCount) {
        this.totalRequestsCount = totalRequestsCount;
    }

    public long getUniqueRequestCount() {
        return uniqueRequestCount;
    }

    public void setUniqueRequestCount(long uniqueRequestCount) {
        this.uniqueRequestCount = uniqueRequestCount;
    }

    public long getInvalidRequestCount() {
        return invalidRequestCount;
    }

    public void setInvalidRequestCount(long invalidRequestCount) {
        this.invalidRequestCount = invalidRequestCount;
    }
}
