# Домашнее задание 2
Вариант #11 <br>
В вашем распоряжении — массив из 100 млн. чисел - отсчётов сигнала ЭКГ, полученных при частоте дискретизации f (например, f=360 Гц). <br>
Составьте последовательный алгоритм подсчета количества R-пиков сигнала, считая, что R-пики - это локальные максимумы сигнала 
по модулю (они могут быть как положительной, так и отрицательной полярности), 
и между соседними R-пиками должно пройти как минимум R_window отсчётов (например, R_window = 115), 
а затем распараллельте его на несколько процессов с учётом оптимизации работы с кэш-памятью.
<hr>
[!][Build Status](https://app.travis-ci.com/xpewa/Technopark-IZ-2021.svg?branch=IZ-2)](https://app.travis-ci.com/xpewa/Technopark-IZ-2021)
