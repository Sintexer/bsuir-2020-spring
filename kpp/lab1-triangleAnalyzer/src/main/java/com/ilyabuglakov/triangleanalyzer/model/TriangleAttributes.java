package com.ilyabuglakov.triangleanalyzer.model;

public class TriangleAttributes {
    Triangle triangle;
    public boolean equilateral, isosceles, rectangular;
    public TriangleAttributes(Triangle triangle, boolean equilateral, boolean isosceles, boolean rectangular){
        this.triangle = triangle;
        this.equilateral = equilateral;
        this.isosceles = isosceles;
        this.rectangular = rectangular;
    }

    public TriangleAttributes(int sd1, int sd2, int sd3, boolean equilateral, boolean isosceles, boolean rectangular){
        this.triangle = new Triangle(sd1, sd2, sd3);
        this.equilateral = equilateral;
        this.isosceles = isosceles;
        this.rectangular = rectangular;
    }

    public Triangle getTriangle() {
        return triangle;
    }

    public void setTriangle(Triangle triangle) {
        this.triangle = triangle;
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

}
