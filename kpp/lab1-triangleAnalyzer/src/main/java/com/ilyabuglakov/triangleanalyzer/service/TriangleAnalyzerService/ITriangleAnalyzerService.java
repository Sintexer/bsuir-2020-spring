package com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService;

import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer.TriangleAnalyzer;

public interface ITriangleAnalyzerService {
    TriangleAnalyzer formResponse(int side1, int side2, int side3);
    boolean isEquilateral(int side1, int side2, int side3);
    boolean isIsosceles(int side1, int side2, int side3);
    boolean isRectangular(int side1, int side2, int side3);
    boolean validate(int side1, int side2, int side3);
}
