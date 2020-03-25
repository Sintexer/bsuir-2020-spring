package com.ilyabuglakov.triangleanalyzer.service.TriangleAnalyzerService;

import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer.TriangleAnalyzer;
import org.springframework.stereotype.Service;

@Service
public class TriangleAnalyzerService implements ITriangleAnalyzerService {

    public TriangleAnalyzer formResponse(int side1, int side2, int side3){
        return new TriangleAnalyzer(
                isEquilateral(side1, side2, side3),
                isIsosceles(side1, side2, side3),
                isRectangular(side1, side2, side3));
    }

    public boolean isEquilateral(int side1, int side2, int side3) {
        return side1 == side2 && side2 == side3;
    }

    public boolean isIsosceles(int side1, int side2, int side3) {
        return side1 == side2 || side2 == side3 || side1 == side3;
    }

    public boolean isRectangular(int side1, int side2, int side3) {
        return rectangularCondition(side1, side2, side3) ||
                rectangularCondition(side2, side3, side1) ||
                rectangularCondition(side1, side3, side2);
    }

    public boolean validate(int side1, int side2, int side3) {
        return validationCondition(side1, side2, side3) &&
                validationCondition(side1, side3, side2) &&
                validationCondition(side2,side3, side1) &&
                (side1>0&&side2>0&&side3>0);
    }

    private boolean validationCondition(int side1, int side2, int side3) {
        return side1 + side2 > side3;
    }

    private boolean rectangularCondition(int side1, int side2, int side3) {
        return Math.pow(side1, 2) + Math.pow(side2, 2) == Math.pow(side3, 2);
    }

}
