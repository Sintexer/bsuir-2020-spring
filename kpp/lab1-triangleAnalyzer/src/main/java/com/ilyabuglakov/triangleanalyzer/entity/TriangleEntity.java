package com.ilyabuglakov.triangleanalyzer.entity;

import com.ilyabuglakov.triangleanalyzer.model.Triangle;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(schema="triangle_analyzer", name="input")
public class TriangleEntity {
    @Id
    @GeneratedValue
    private long id;

    @GeneratedValue
    private long processId;

    private int side1;
    private int side2;
    private int side3;

    public TriangleEntity(){}

    public TriangleEntity(int s1, int s2, int s3){
        side1 = s1;
        side2 = s2;
        side3 = s3;
    }

    public TriangleEntity(Long processId, int s1, int s2, int s3){
        this.processId = processId;
        side1 = s1;
        side2 = s2;
        side3 = s3;
    }

    public TriangleEntity(Long processId, Triangle t){
        this.processId = processId;
        side1 = t.getSide1();
        side2 = t.getSide2();
        side3 = t.getSide3();
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

    public void setProcessId(long processId) {
        this.processId = processId;
    }

    public int getSide1() {
        return side1;
    }

    public void setSide1(int side1) {
        this.side1 = side1;
    }

    public int getSide2() {
        return side2;
    }

    public void setSide2(int side2) {
        this.side2 = side2;
    }

    public int getSide3() {
        return side3;
    }

    public void setSide3(int side3) {
        this.side3 = side3;
    }
}
