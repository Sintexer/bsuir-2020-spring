package com.ilyabuglakov.triangleanalyzer.entity;


import com.ilyabuglakov.triangleanalyzer.model.TriangleAttributes;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(schema = "triangle_analyzer", name = "attributes")
public class TriangleAttributesEntity {

    @Id
    @GeneratedValue
    private Long id;

    private Long processId;
    private boolean equilateral, isosceles, rectangular;
    private int side1, side2, side3;

    public TriangleAttributesEntity() {}

    public TriangleAttributesEntity(Long processId, boolean equilateral, boolean isosceles, boolean rectangular, int side1, int side2, int side3){
        this.processId = processId;
        this.equilateral = equilateral;
        this.isosceles = isosceles;
        this.rectangular = rectangular;
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }

    public TriangleAttributesEntity(Long processId, TriangleAttributes t){
        this.processId = processId;
        this.equilateral = t.equilateral;
        this.isosceles = t.isosceles;
        this.rectangular = t.rectangular;
        this.side1 = t.getTriangle().getSide1();
        this.side2 = t.getTriangle().getSide2();
        this.side3 = t.getTriangle().getSide3();
    }

    public TriangleAttributesEntity(TriangleAttributes t){
        this.equilateral = t.equilateral;
        this.isosceles = t.isosceles;
        this.rectangular = t.rectangular;
        this.side1 = t.getTriangle().getSide1();
        this.side2 = t.getTriangle().getSide2();
        this.side3 = t.getTriangle().getSide3();
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

    public boolean isEquilateral() {
        return equilateral;
    }

    public void setEquilateral(boolean equilateral) {
        this.equilateral = equilateral;
    }

    public boolean isIsosceles() {
        return isosceles;
    }

    public void setIsosceles(boolean isosceles) {
        this.isosceles = isosceles;
    }

    public boolean isRectangular() {
        return rectangular;
    }

    public void setRectangular(boolean rectangular) {
        this.rectangular = rectangular;
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
