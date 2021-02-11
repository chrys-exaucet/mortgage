//
// Created by @chrys on 2/11/2021.
//

#ifndef UNTITLED_ADDRESS_H
#define UNTITLED_ADDRESS_H


enum ERoadType {
    LARGE,
    SMALL,
    EMPTY
} RoadType;

typedef struct road {
    int number;
    enum ERoadType type;
} road_t;

typedef struct address {
    road_t road;
    char *city;
    char *postalCode;
} address_t;

#endif //UNTITLED_ADDRESS_H
