import cv2
import numpy as np

# Definir los rangos de colores para cada fluido
# Se define en HSV
fluidos = {
    'Agua': ([90, 100, 100], [110, 255, 255]),
    'Aceite': ([20, 100, 100], [40, 255, 255]),
    'Leche': ([0, 0, 200], [20, 50, 255]),
    'Vino': ([145, 50, 50], [165, 255, 150]),
    'Cafe': ([0, 50, 50], [20, 200, 200]),
    'Te': ([20, 100, 60], [40, 255, 150]),
}

def reconocer_fluido(imagen):
    # Convertir la imagen de RGB a HSV
    hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
    # Iterar sobre los rangos de colores de los fluidos
    for fluido, (lower, upper) in fluidos.items():
        # Crear una máscara para el rango de colores del fluido actual
        mask = cv2.inRange(hsv, np.array(lower), np.array(upper))
        # Contar los píxeles blancos en la máscara
        cantidad_pixeles = cv2.countNonZero(mask)
        # Si la cantidad de píxeles blancos es mayor a un umbral, se considera que el fluido está presente
        umbral = 1000  # Ajusta este valor según las necesidades
        if cantidad_pixeles > umbral:
            return fluido
    # Si no se encontró ningún fluido, retornar None
    return None

# Cargar la imagen de prueba
imagen_prueba = cv2.imread('Proyecto\Fluido5.jpg')

# Llamar a la función para reconocer el fluido en la imagen
resultado = reconocer_fluido(imagen_prueba)

# Imprimir el resultado
if resultado:
    print('El fluido es:', resultado)
    # Agregar texto al resultado en la imagen
    cv2.putText(imagen_prueba, resultado, (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
else:
    print('No se encontró ningún fluido en la imagen.')
    # Agregar texto al resultado en la imagen
    cv2.putText(imagen_prueba, "No es un fluido", (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

# Mostrar la imagen con el resultado en una ventana emergente
cv2.imshow('Resultado', imagen_prueba)
cv2.waitKey(0)
cv2.destroyAllWindows()