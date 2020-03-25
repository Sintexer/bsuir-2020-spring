package com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;

public interface ITriangleAnalyzer {
    public boolean isEquilateral();
    public void setEquilateral(boolean equilateral);
    public boolean isIsosceles();
    public void setIsosceles(boolean isosceles);
    public boolean isRectangular();
    public void setRectangular(boolean rectangular);
}
