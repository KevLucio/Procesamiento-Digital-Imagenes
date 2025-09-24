import cv2
import numpy as np

# Cargar la imagen de entrada en color
imagen_color = cv2.imread('Practicas\Imagen1P6.jpg')

# Verificar que la imagen se haya cargado correctamente
if imagen_color is None:
    print("No se pudo cargar la imagen.")
    exit()

# Convertir la imagen a escala de grises
imagen_grises = cv2.cvtColor(imagen_color, cv2.COLOR_BGR2GRAY)

# Crear una imagen en blanco y negro con detalles en rojo y azul
imagen_resultante = cv2.cvtColor(imagen_grises, cv2.COLOR_GRAY2BGR)

# Obtener los canales de color de la imagen resultante
canal_rojo = imagen_resultante[:, :, 2]
canal_azul = imagen_resultante[:, :, 0]

# Establecer los valores de los canales de color
canal_rojo[:,:] = 255  # Configurar el canal rojo a 0 (sin rojo)
canal_azul[:,:] = 255  # Configurar el canal azul a 255 (máximo azul)

# Mostrar las imágenes originales y la imagen resultante
cv2.imshow('Imagen en color', imagen_color)
cv2.imshow('Imagen en escala de grises', imagen_grises)
cv2.imshow('Imagen resultado', imagen_resultante)
cv2.waitKey(0)
cv2.destroyAllWindows()