package com.ilyabuglakov.triangleanalyzer.config;

import com.ilyabuglakov.triangleanalyzer.controller.TriangleAnalyzerController;
import com.ilyabuglakov.triangleanalyzer.model.TriangleAnalyzer;
import com.ilyabuglakov.triangleanalyzer.service.DefaultTriangleAnalyzerService;
import org.mockito.Mockito;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
import org.springframework.context.annotation.Profile;

@Profile("test")
@Configuration
public class TestSpringConfig {
    @Bean
    @Primary
    public DefaultTriangleAnalyzerService service(){
        return Mockito.mock(DefaultTriangleAnalyzerService.class);
    }
}
