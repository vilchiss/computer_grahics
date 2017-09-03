#!/usr/bin/python
# -*- coding: utf-8 -*-
# Universidad Nacional Autonoma de Mexico / Facultad de Ingenieria
# Computación Gráfica
# Alumnos:
# Barriga Martínez Diego Alberto
# Vilchis Oropeza Luis Alberto
# Hecho en Python 3.5


class Window:
    def __init__(self):
        self.point = []
        self.height = 0
        self.width = 0


def get_data():
    points = list()
    tmp = list()
    file = open('input.txt', 'r')
    content = file.readline()
    while content != "":
        content = content.rstrip('\n')
        for number in content.split(" "):
            tmp.append(int(number))
        points.append(tmp)
        tmp = []
        content = file.readline()
    file.close()

    return points


def left_analysis(point_1, point_2):
    print(point_1, point_2)


def line_clipper(points):
    i = 0
    while i < len(points) - 1:
        left_analysis(points[i], points[i+1])
        i += 1


def main():
    points = get_data()
    window = input()
    line_clipper(points)


if __name__ == '__main__':
    main()