package com.ilyabuglakov.triangleanalyzer.entity;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(schema = "triangle_analyzer", name="process_id")
public class ProcessIdEntity {
    @Id
    @GeneratedValue
    private Long id;

    private Long processId;
    private String status;

    public ProcessIdEntity () {}

    public ProcessIdEntity(Long processId, String status){
        this.processId = processId;
        this.status = status;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getProcessId() {
        return processId;
    }

    public void setProcessId(Long processId) {
        this.processId = processId;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
