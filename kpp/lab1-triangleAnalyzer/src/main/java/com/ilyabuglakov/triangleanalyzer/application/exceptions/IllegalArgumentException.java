package com.ilyabuglakov.triangleanalyzer.application.exceptions;

//import org.springframework.http.HttpStatus;
//import org.springframework.web.bind.annotation.ResponseStatus;
//
//@ResponseStatus(value= HttpStatus.BAD_REQUEST, reason="Provided sides can't form a triangle") //400
public class IllegalArgumentException extends RuntimeException {

    public IllegalArgumentException(String message) {
        super(message);
    }

    public IllegalArgumentException(String message, Throwable cause) {
        super(message, cause);
    }

}
