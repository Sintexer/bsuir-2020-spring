package com.ilyabuglakov.triangleanalyzer.service;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.IllegalArgumentException;

public class Validator{
    static public void validate(int sd1, int sd2, int sd3)
    throws IllegalArgumentException{
        if (!validateHelper(sd1, sd2, sd3)) {
            throw new IllegalArgumentException(
                    String.format("Provided sides can't form a triangle:" +
                            " side1=%d, side2=%d, side3=%d", sd1, sd2, sd3));
        }
    }

    private static boolean validateHelper(int side1, int side2, int side3) {
        return validationCondition(side1, side2, side3) &&
                validationCondition(side1, side3, side2) &&
                validationCondition(side2,side3, side1) &&
                (side1>0&&side2>0&&side3>0);
    }

    private static boolean validationCondition(int side1, int side2, int side3) {
        return side1 + side2 > side3;
    }
}
