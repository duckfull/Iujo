#include <stdio.h>
#include <string.h>

int totalClientes = 0;
float montoBrutoTotal = 0.0;
float totalDescuentos = 0.0;

int totalUnidadesBebidas = 0;
int totalUnidadesSnacks = 0;
int totalUnidadesPapeleria = 0;

int cantB001 = 0; /* Jugo */
int cantB002 = 0; /* Agua */
int cantS001 = 0; /* Papas */
int cantP001 = 0; /* Cuaderno */
int cantP002 = 0; /* Lapiz */

float ventaMaxima = 0.0;
int clienteVentaMaxima = 0;
float ventaMinima = 0.0;
int clienteVentaMinima = 0;

void registrarVenta(void);
void verReporteDia(void);
void verProductoMasVendido(void);
void procesarProducto(char codigo[], int cantidad, float *subtotalCliente, int *unidadesCliente, int *prodDistintosValidos, int *prodValido);

int main(void) {
    int opcion = 0;

    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("       CAJARAPIDA - TIENDA ESCOLAR       \n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("1. Registrar venta de un cliente\n");
        printf("2. Ver reporte del dia\n");
        printf("3. Ver producto mas vendido\n");
        printf("4. Salir\n");
        printf("\n");
        printf("> Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarVenta();
                break;
            case 2:
                verReporteDia();
                break;
            case 3:
                verProductoMasVendido();
                break;
            case 4:
                printf("\nSaliendo del programa de forma ordenada...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}

void procesarProducto(char codigo[], int cantidad, float *subtotalCliente, int *unidadesCliente, int *prodDistintosValidos, int *prodValido) {
    float precio = 0.0;
    int categoria = 0; /* 1 = Bebida, 2 = Snack, 3 = Papeleria */
    int existe = 0;

    if (strcmp(codigo, "B001") == 0) {
        precio = 1.50; categoria = 1; existe = 1;
    } else if (strcmp(codigo, "B002") == 0) {
        precio = 0.80; categoria = 1; existe = 1;
    } else if (strcmp(codigo, "S001") == 0) {
        precio = 1.20; categoria = 2; existe = 1;
    } else if (strcmp(codigo, "P001") == 0) {
        precio = 2.50; categoria = 3; existe = 1;
    } else if (strcmp(codigo, "P002") == 0) {
        precio = 0.60; categoria = 3; existe = 1;
    }

    if (!(cantidad > 0) || !existe) {
        printf(" Error: Cantidad invalida o codigo inexistente en el catalogo. Registro cancelado.\n");
        *prodValido = 0;
        return;
    }

    *prodValido = 1;
    float costoProducto = precio * cantidad;
    *subtotalCliente += costoProducto;
    *unidadesCliente += cantidad;
    (*prodDistintosValidos)++;

    if (strcmp(codigo, "B001") == 0) cantB001 += cantidad;
    else if (strcmp(codigo, "B002") == 0) cantB002 += cantidad;
    else if (strcmp(codigo, "S001") == 0) cantS001 += cantidad;
    else if (strcmp(codigo, "P001") == 0) cantP001 += cantidad;
    else if (strcmp(codigo, "P002") == 0) cantP002 += cantidad;

    switch (categoria) {
        case 1:
            totalUnidadesBebidas += cantidad;
            break;
        case 2:
            totalUnidadesSnacks += cantidad;
            break;
        case 3:
            totalUnidadesPapeleria += cantidad;
            break;
    }

    printf("> Importe parcial: %.2f\n", costoProducto);
}

void registrarVenta(void) {
    int esEstudiante = 0;
    int numProductos = 0;
    float subtotalCliente = 0.0;
    int totalUnidadesCliente = 0;
    int prodDistintosValidos = 0;

    totalClientes++;
    printf("\n>>> CLIENTE #%d\n", totalClientes);
    
    printf("Es estudiante? (1=Si/0=No): ");
    scanf("%d", &esEstudiante);

    printf("Cuantos productos distintos va a comprar?: ");
    scanf("%d", &numProductos);

    int i = 0;
    for (i = 1; i <= numProductos; i++) {
        char codigo[10];
        int cantidad = 0;
        int prodValido = 0;

        printf("\n> Producto %d\n", i);
        printf("Codigo: ");
        scanf("%s", codigo);
        printf("Cantidad: ");
        scanf("%d", &cantidad);

        procesarProducto(codigo, cantidad, &subtotalCliente, &totalUnidadesCliente, &prodDistintosValidos, &prodValido);
        
        if (!prodValido) {
            printf("Reintentar este producto? (1=Si - 0=No): ");
            int reintentar = 0;
            scanf("%d", &reintentar);
            if (reintentar == 1) {
                i--; 
            }
        }
    }

    float descuento = 0.0;

    if ((subtotalCliente > 50.0) && (esEstudiante == 1)) {
        descuento = subtotalCliente * 0.10;
    }

    if ((subtotalCliente > 100.0) || (totalUnidadesCliente > 15)) {
        printf("\n Regalo: El cliente se ha ganado un lapiz de regalo!\n");
    }

    int condicionMontoVIP = (subtotalCliente >= 80.0);
    int condicionCantVIP = (prodDistintosValidos >= 5);
    if ((condicionMontoVIP && condicionCantVIP) || (!condicionMontoVIP && !condicionCantVIP)) {
        if (condicionMontoVIP && condicionCantVIP) {
            printf(" Estado: El cliente es VIP!\n");
        }
    }

    int condicionMontoEnvio = (subtotalCliente > 50.0);
    int esEnvioGratis = 1;
    if ((condicionMontoEnvio && esEnvioGratis) || (!condicionMontoEnvio && !esEnvioGratis)) {
        if (condicionMontoEnvio) {
            printf(" Envio: Aplica envio gratis!\n");
        }
    }

    float totalAPagar = subtotalCliente - descuento;

    montoBrutoTotal += subtotalCliente;
    totalDescuentos += descuento;

    if (totalClientes == 1) {
        ventaMaxima = totalAPagar;
        clienteVentaMaxima = 1;
        ventaMinima = totalAPagar;
        clienteVentaMinima = 1;
    } else {
        if (totalAPagar > ventaMaxima) {
            ventaMaxima = totalAPagar;
            clienteVentaMaxima = totalClientes;
        }
        if (totalAPagar < ventaMinima) {
            ventaMinima = totalAPagar;
            clienteVentaMinima = totalClientes;
        }
    }

    printf("\nSubtotal         : %.2f\n", subtotalCliente);
    printf("Descuento        : %.2f\n", descuento);
    printf("TOTAL A PAGAR    : %.2f\n", totalAPagar);
}

void verReporteDia(void) {
    if (totalClientes == 0) {
        printf("\nNo se han registrado ventas en el dia.\n");
        return;
    }

    float montoNetoTotal = montoBrutoTotal - totalDescuentos;
    float promedioGasto = montoNetoTotal / totalClientes;
    
    float porcDescuento = 0.0;
    if (montoBrutoTotal > 0) {
        porcDescuento = (totalDescuentos / montoBrutoTotal) * 100.0;
    }

    int totalUnidadesCat = totalUnidadesBebidas + totalUnidadesSnacks + totalUnidadesPapeleria;
    float porcBebidas = 0.0, porcSnacks = 0.0, porcPapeleria = 0.0;

    if (totalUnidadesCat > 0) {
        porcBebidas = ((float)totalUnidadesBebidas / totalUnidadesCat) * 100.0;
        porcSnacks = ((float)totalUnidadesSnacks / totalUnidadesCat) * 100.0;
        porcPapeleria = ((float)totalUnidadesPapeleria / totalUnidadesCat) * 100.0;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("   REPORTE FINAL DEL DIA - CAJARAPIDA   \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("Clientes atendidos     : %d\n", totalClientes);
    printf("Monto bruto total      : %.2f\n", montoBrutoTotal);
    printf("Descuentos otorgados   : %.2f (%.2f%%)\n", totalDescuentos, porcDescuento);
    printf("\n");
    printf("MONTO NETO RECAUDADO   : %.2f\n", montoNetoTotal);
    printf("\n");
    printf("Promedio por cliente   : %.2f\n", promedioGasto);
    printf("Venta maxima           : %.2f (Cliente #%d)\n", ventaMaxima, clienteVentaMaxima);
    printf("Venta minima           : %.2f (Cliente #%d)\n", ventaMinima, clienteVentaMinima);
    printf("\n");
    printf("\nVENTAS POR CATEGORIA\n");
    printf("Bebidas:   %d unidades > %.2f%%\n", totalUnidadesBebidas, porcBebidas);
    printf("Snacks:    %d unidades > %.2f%%\n", totalUnidadesSnacks, porcSnacks);
    printf("Papeleria: %d unidades > %.2f%%\n", totalUnidadesPapeleria, porcPapeleria);
}

void verProductoMasVendido(void) {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("         PRODUCTOS MAS VENDIDOS          \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("Jugo     (B001): %d unidades\n", cantB001);
    printf("Agua     (B002): %d unidades\n", cantB002);
    printf("Papas    (S001): %d unidades\n", cantS001);
    printf("Cuaderno (P001): %d unidades\n", cantP001);
    printf("Lapiz    (P002): %d unidades\n", cantP002);

    int maxUnidades = cantB001;
    char nombreMax[20] = "Jugo";
    char codigoMax[10] = "B001";

    if (cantB002 > maxUnidades) {
        maxUnidades = cantB002;
        strcpy(nombreMax, "Agua");
        strcpy(codigoMax, "B002");
    }
    if (cantS001 > maxUnidades) {
        maxUnidades = cantS001;
        strcpy(nombreMax, "Papas");
        strcpy(codigoMax, "S001");
    }
    if (cantP001 > maxUnidades) {
        maxUnidades = cantP001;
        strcpy(nombreMax, "Cuaderno");
        strcpy(codigoMax, "P001");
    }
    if (cantP002 > maxUnidades) {
        maxUnidades = cantP002;
        strcpy(nombreMax, "Lapiz");
        strcpy(codigoMax, "P002");
    }

    if (maxUnidades == 0) {
        printf("\n>>> Aún no se han vendido unidades.\n");
    } else {
        printf("\n>>> Producto mas Vendido: %s (%s) con %d unidades\n", nombreMax, codigoMax, maxUnidades);
    }
}
