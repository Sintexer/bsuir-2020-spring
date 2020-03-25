package com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;

public class TriangleAnalyzer implements ITriangleAnalyzer {
    public boolean equilateral, isosceles, rectangular;
    public TriangleAnalyzer(boolean equilateral, boolean isosceles, boolean rectangular){
        this.equilateral = equilateral;
        this.isosceles = isosceles;
        this.rectangular = rectangular;
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
