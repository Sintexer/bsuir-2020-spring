package com.ilyabuglakov.triangleanalyzer.application.handlers;

import com.ilyabuglakov.triangleanalyzer.application.exceptions.OperationNotImplementedException;
import org.springframework.http.ResponseEntity;
import org.springframework.util.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;
import com.ilyabuglakov.triangleanalyzer.application.exceptions.InternalServerErrorException;

public class OperationNotImplementedExceptionHandlerTest {

    private OperationNotImplementedExceptionHandler handler;

    @BeforeMethod
    void init(){
        handler = new OperationNotImplementedExceptionHandler();
    }

    @Test
    public void testHandleExceptionWithoutMessage() {
        ResponseEntity<?> response = handler.handle( new OperationNotImplementedException(""));
        Assert.notNull(response, "");
    }

    @Test
    public void testHandleExceptionWithMessage(){
        ResponseEntity<?> response = handler.handle(new OperationNotImplementedException("Internal Server Error"));
        Assert.notNull(response, "");
    }
}