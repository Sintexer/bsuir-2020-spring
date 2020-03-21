package com.ilyabuglakov.triangleanalyzer.service;

public interface ITriangleAnalyzerService {
    boolean isEquilateral(int side1, int side2, int side3);
    boolean isIsosceles(int side1, int side2, int side3);
    boolean isRectangular(int side1, int side2, int side3);
    boolean validate(int side1, int side2, int side3);
}
