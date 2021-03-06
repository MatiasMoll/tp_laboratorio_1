#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile FILE* recibe el puntero al FILE que contiene los datos de los empleados
 * \param pArrayListEmployee LinkedList* LinkedList a llenar con el FILE
 * \return int retorno [-1]Si el pFile es NULL o si la LinkedList es NULL
                        [0]Si la carga fue correcta
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char bufferId[4096];
    char bufferNombre[4096];
    char bufferHorasTrabajadas[4096];
    char bufferSueldo[4096];
    Employee* pAuxEmployee;
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        while(!feof(pFile))
        {
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            pAuxEmployee = employee_newParametros(bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            if(pAuxEmployee != NULL)
            {
                ll_add(pArrayListEmployee,pAuxEmployee);
                retorno = 0;
            }

        }
        fclose(pFile);
    }
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile FILE* recibe el puntero al FILE que contiene los datos de los empleados
 * \param pArrayListEmployee LinkedList* LinkedList a llenar con el FILE
 * \return int retorno [-1]Si el pFile es NULL o si la LinkedList es NULL
                        [0]Si la carga fue correcta
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee aux;
    Employee* empleado;
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        while(!feof(pFile))
        {

            empleado = employee_newFileBinario(aux);
            fread(&aux,sizeof(Employee),1,pFile);
            if(empleado != NULL)
            {
                ll_add(pArrayListEmployee,empleado);
            }
            else
            {
                employee_delete(empleado);
            }
        }
        retorno = 0;
    }
    fclose(pFile);
    return retorno;
}
