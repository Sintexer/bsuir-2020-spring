package com.ilyabuglakov.triangleanalyzer.model;

public class TriangleAttributesBuilder{
    private Triangle triangle;
    private boolean equilateral, isosceles, rectangular;

    public void setEquilateral(boolean equilateral) {
        this.equilateral = equilateral;
    }

    public void setIsosceles(boolean isosceles) {
        this.isosceles = isosceles;
    }

    public void setRectangular(boolean rectangular) {
        this.rectangular = rectangular;
    }

    public void setTriangle(Triangle t){
        triangle = t;
    }

    public void reset(){
        triangle = null;
        equilateral = false;
        isosceles = false;
        rectangular = false;
    }

    public TriangleAttributes build(){
        TriangleAttributes result = new TriangleAttributes();
        result.setEquilateral(equilateral);
        result.setIsosceles(isosceles);
        result.setRectangular(rectangular);
        result.setTriangle(triangle);
        return result;
    }
}