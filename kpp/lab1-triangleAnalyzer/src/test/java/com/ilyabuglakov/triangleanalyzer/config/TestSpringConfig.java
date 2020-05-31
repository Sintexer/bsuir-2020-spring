package com.ilyabuglakov.triangleanalyzer.config;

import com.ilyabuglakov.triangleanalyzer.service.analyzer.TriangleAnalyzerService;
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
    public TriangleAnalyzerService service(){
        return Mockito.mock(TriangleAnalyzerService.class);
    }
}
