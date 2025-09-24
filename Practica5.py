import cv2
import numpy as np

# Cargar las imágenes de entrada
imagen1 = cv2.imread('Practicas\Imagen1P4.jpg')
imagen2 = cv2.imread('Practicas\Imagen2P4.jpg')

# Verificar que las imágenes se hayan cargado correctamente
if imagen1 is None or imagen2 is None:
    print("No se pudieron cargar las imágenes.")
    exit()

# Asegurarse de que ambas imágenes tengan el mismo tamaño
if imagen1.shape != imagen2.shape:
    print("Las imágenes deben tener el mismo tamaño.")
    exit()

# Sumar las imágenes pixel a pixel
suma = cv2.add(imagen1, imagen2)

# Restar las imágenes pixel a pixel
resta = cv2.subtract(imagen1, imagen2)

# Multiplicar las imágenes pixel a pixel
multiplicacion = cv2.multiply(imagen1, imagen2)

# Realizar la operación lógica OR entre las imágenes
or_logico = cv2.bitwise_or(imagen1, imagen2)

# Realizar la operación lógica AND entre las imágenes
and_logico = cv2.bitwise_and(imagen1, imagen2)

# Mostrar las imágenes resultantes
cv2.imshow('Suma', suma)
cv2.imshow('Resta', resta)
cv2.imshow('Multiplicacion', multiplicacion)
cv2.imshow('OR Logico', or_logico)
cv2.imshow('AND Logico', and_logico)
cv2.waitKey(0)
cv2.destroyAllWindows()
