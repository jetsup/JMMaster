#pragma once

#include <Arduino.h>

#include <JMConfig.hpp>
#include <JMNetworking.hpp>
#include <JMServer.hpp>

// Multi core support
extern TaskHandle_t Task1;
extern TaskHandle_t Task2;

extern Networking network;

/**
 * Task to run on core 0. This core is responsible for checking the network and
 * other system monitoring tasks
 * @param pvParameters The parameters to pass to the task
 */
void monitoringTask(void *pvParameters);

/**
 * Task to run on core 1. This core is responsible for running the main
 * application logic
 * @param pvParameters The parameters to pass to the task
 */
void executorTask(void *pvParameters);


