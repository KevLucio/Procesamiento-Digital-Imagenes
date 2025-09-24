import cv2
import numpy as np

def reflection(image):
    reflected = cv2.flip(image, 1)
    return reflected

def resize(image, scale_percent):
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    resized = cv2.resize(image, (width, height), interpolation=cv2.INTER_AREA)
    return resized

def crop(image, x, y, width, height):
    cropped = image[y:y+height, x:x+width]
    return cropped

def rotate(image, angle):
    height, width = image.shape[:2]
    rotation_matrix = cv2.getRotationMatrix2D((width/2, height/2), angle, 1)
    rotated = cv2.warpAffine(image, rotation_matrix, (width, height))
    return rotated

def negative(image):
    inverted = 255 - image
    return inverted

def threshold(image, threshold_value):
    _, thresholded = cv2.threshold(image, threshold_value, 255, cv2.THRESH_BINARY)
    return thresholded

# Carga la imagen de entrada
image_path = 'Practicas\Imagen1P4.jpg'
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# Aplica las transformaciones geométricas
reflected_image = reflection(image)
expanded_image = resize(image, 150)
cropped_image = crop(image, 100, 100, 300, 300)
rotated_image = rotate(image, 45)

# Aplica otras operaciones
negative_image = negative(image)
thresholded_image = threshold(image, 127)

# Muestra las imágenes resultantes
cv2.imshow('Original', image)
cv2.imshow('Reflexion', reflected_image)
cv2.imshow('Expandida', expanded_image)
cv2.imshow('Cortada', cropped_image)
cv2.imshow('Rotada', rotated_image)
cv2.imshow('Negativo', negative_image)
cv2.imshow('Umbralizado', thresholded_image)
cv2.waitKey(0)
cv2.destroyAllWindows()