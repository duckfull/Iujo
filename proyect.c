#include <stdio.h>

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

int main(void) {
    int opcion = 0;

    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("       CAJARAPIDA - TIENDA ESCOLAR       \n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Registrar venta de un cliente\n");
        printf("2. Ver reporte del dia\n");
        printf("3. Ver producto mas vendido\n");
        printf("4. Salir\n");
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

void registrarVenta(void) {
    int esEstudiante = 0;
    int numProductos = 0;
    float subtotalCliente = 0.0;
    int totalUnidadesCliente = 0;
    int prodDistintosValidos = 0;

    totalClientes++;
    printf("\n>>> CLIENTE #%d\n", totalClientes);
    
    printf("Es estudiante? (1=Si / 0=No): ");
    scanf("%d", &esEstudiante);

    printf("Cuantos productos distintos va a comprar?: ");
    scanf("%d", &numProductos);

    int i = 1;
    while (i <= numProductos) {
        int codigo = 0;
        int cantidad = 0;
        float precio = 0.0;
        int categoria = 0; /* 1=Bebida, 2=Snack, 3=Papeleria */
        int existe = 0;

        printf("\n> Producto %d\n", i);
        printf(" Catalogos de codigos:\n");
        printf("  1 = B001 (Jugo)\n");
        printf("  2 = B002 (Agua)\n");
        printf("  3 = S001 (Papas)\n");
        printf("  4 = P001 (Cuaderno)\n");
        printf("  5 = P002 (Lapiz)\n");
        printf("Ingrese el numero de codigo: ");
        scanf("%d", &codigo);

        printf("Cantidad: ");
        scanf("%d", &cantidad);

        if (codigo == 1) {
            precio = 1.50; categoria = 1; existe = 1;
        } else if (codigo == 2) {
            precio = 0.80; categoria = 1; existe = 1;
        } else if (codigo == 3) {
            precio = 1.20; categoria = 2; existe = 1;
        } else if (codigo == 4) {
            precio = 2.50; categoria = 3; existe = 1;
        } else if (codigo == 5) {
            precio = 0.60; categoria = 3; existe = 1;
        }

        if (!(cantidad > 0) || !existe) {
            printf("\n [!] Error: Cantidad invalida o codigo inexistente. Intente de nuevo.\n");
            continue; 
        }

        if (codigo == 1) cantB001 += cantidad;
        else if (codigo == 2) cantB002 += cantidad;
        else if (codigo == 3) cantS001 += cantidad;
        else if (codigo == 4) cantP001 += cantidad;
        else if (codigo == 5) cantP002 += cantidad;

        switch (categoria) {
            case 1: totalUnidadesBebidas += cantidad; break;
            case 2: totalUnidadesSnacks += cantidad; break;
            case 3: totalUnidadesPapeleria += cantidad; break;
        }

        float costoProducto = precio * cantidad;
        subtotalCliente += costoProducto;
        totalUnidadesCliente += cantidad;
        prodDistintosValidos++;

        printf("> Importe parcial: %.2f\n", costoProducto);
        i++;
    }

    float descuento = 0.0;

    if ((subtotalCliente > 50.0) && (esEstudiante == 1)) {
        descuento = subtotalCliente * 0.10;
    }

    if ((subtotalCliente > 100.0) || (totalUnidadesCliente > 15)) {
        printf("\n Regalo: El cliente se ha ganado un lapiz de regalo!\n");
    }

    int esMayor80 = (subtotalCliente >= 80.0);
    int lleva5Prod = (prodDistintosValidos >= 5);

    if ((esMayor80 && lleva5Prod) || (!esMayor80 && !lleva5Prod)) {
        if (esMayor80 && lleva5Prod) {
            printf(" Estado: El cliente es VIP!\n");
        }
    }

    int supera50 = (subtotalCliente > 50.0);
    int tieneEnvio = 1;
    if ((supera50 && tieneEnvio) || (!supera50 && !tieneEnvio)) {
        if (supera50) {
            printf(" Envio: Aplica envio gratis!\n");
            printf(" Sera enviado por @AliExpress & @IujoExpress!\n");
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

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("   REPORTE FINAL DEL DIA - CAJARAPIDA   \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Clientes atendidos     : %d\n", totalClientes);
    printf("Monto bruto total      : %.2f\n", montoBrutoTotal);
    printf("Descuentos otorgados   : %.2f (%.2f%%)\n", totalDescuentos, porcDescuento);
    printf("\nMONTO NETO RECAUDADO   : %.2f\n", montoNetoTotal);
    printf("\nPromedio por cliente   : %.2f\n", promedioGasto);
    printf("Venta maxima           : %.2f (Cliente #%d)\n", ventaMaxima, clienteVentaMaxima);
    printf("Venta minima           : %.2f (Cliente #%d)\n", ventaMinima, clienteVentaMinima);
    printf("\nVENTAS POR CATEGORIA\n");
    printf("Bebidas:   %d unidades > %.2f%%\n", totalUnidadesBebidas, porcBebidas);
    printf("Snacks:    %d unidades > %.2f%%\n", totalUnidadesSnacks, porcSnacks);
    printf("Papeleria: %d unidades > %.2f%%\n", totalUnidadesPapeleria, porcPapeleria);
}

void verProductoMasVendido(void) {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("         PRODUCTOS MAS VENDIDOS          \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. Jugo     (B001): %d unidades\n", cantB001);
    printf("2. Agua     (B002): %d unidades\n", cantB002);
    printf("3. Papas    (S001): %d unidades\n", cantS001);
    printf("4. Cuaderno (P001): %d unidades\n", cantP001);
    printf("5. Lapiz    (P002): %d unidades\n", cantP002);

    int maxUnidades = cantB001;

    if (cantB002 > maxUnidades) maxUnidades = cantB002;
    if (cantS001 > maxUnidades) maxUnidades = cantS001;
    if (cantP001 > maxUnidades) maxUnidades = cantP001;
    if (cantP002 > maxUnidades) maxUnidades = cantP002;

    if (maxUnidades == 0) {
        printf("\n>>> Aún no se han vendido unidades.\n");
        return;
    }

    printf("\n>>> PRODUCTO(S) MAS VENDIDO(S) (%d unidades):\n", maxUnidades);
    if (cantB001 == maxUnidades) printf(" - Jugo (B001)\n");
    if (cantB002 == maxUnidades) printf(" - Agua (B002)\n");
    if (cantS001 == maxUnidades) printf(" - Papas (S001)\n");
    if (cantP001 == maxUnidades) printf(" - Cuaderno (P001)\n");
    if (cantP002 == maxUnidades) printf(" - Lapiz (P002)\n");
}
