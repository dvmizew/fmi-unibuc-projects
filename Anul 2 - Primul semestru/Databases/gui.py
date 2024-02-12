import mysql.connector
from prettytable import PrettyTable

# conexiunea la baza de date
db = mysql.connector.connect(
    host="localhost",
    user="root",
    passwd="ciscosecpa55",
    database="transport_public"
)


def get_sort_option(table_name):
    cursor = db.cursor()
    cursor.execute(f"SHOW COLUMNS FROM {table_name}")
    columns = [column[0] for column in cursor.fetchall()]

    print(f"Coloane disponibile pentru sortare în tabela {table_name}: {', '.join(columns)}")

    sort_option = input("Introduceti numele coloanei pentru sortare (lasati gol pentru a nu sorta): ")
    return sort_option


def list_all_tables():
    cursor = db.cursor(dictionary=True)

    tables = ['Angajati', 'Clienti', 'ParcareAutovehicule', 'Autovehicule', 'Statii', 'Abonamente', 'LiniiAutovehicule']

    for table in tables:
        print(f"\n*** {table} ***")
        sort_option = get_sort_option(table)

        # Construim comanda SQL pentru listare cu optiunea de sortare
        query = f"SELECT * FROM {table}"
        if sort_option:
            query += f" ORDER BY {sort_option}"
        cursor.execute(query)
        result = cursor.fetchall()

        # Afisarea datelor cu PrettyTable
        if result:
            table = PrettyTable(result[0].keys())
            for row in result:
                table.add_row(row.values())
            print(table)
        else:
            print("Tabelul este gol.")


def edit_record(table_name, record_id):
    cursor = db.cursor(dictionary=True)

    print(f"\n*** Modificare inregistrare in tabela {table_name} ***")

    # Obtinem numele coloanelor in tabela respectiva
    cursor.execute(f"SELECT * FROM {table_name}")
    columns = [column[0] for column in cursor.description]
    cursor.fetchall()  # Eliberam rezultatele

    # Afisam informatii despre inregistrarea curenta
    cursor.execute(f"SELECT * FROM {table_name} WHERE ID_{table_name} = {record_id}")
    current_record = cursor.fetchone()

    if not current_record:
        print(f"Nu exista inregistrarea cu ID {record_id} in tabela {table_name}.")
        db.close()
        return

    print("\nInformatii actuale:")
    for column in columns:
        print(f"{column}: {current_record[column]}")

    # Obtinem noile valori pentru coloane
    new_values = {}
    for column in columns:
        if column != f"ID_{table_name}":
            new_value = input(
                f"Introduceti noua valoare pentru {column} (lasati gol pentru a mentine valoarea curenta): ")
            new_values[column] = new_value

    # Construim comanda SQL pentru actualizare
    update_query = f"UPDATE {table_name} SET "
    for column, new_value in new_values.items():
        if new_value:
            update_query += f"{column} = '{new_value}', "
    update_query = update_query.rstrip(", ")  # Eliminam ultima virgula
    update_query += f" WHERE ID_{table_name} = {record_id}"

    try:
        cursor.execute(update_query)
        db.commit()
        print("Inregistrare actualizata cu succes.")
    except mysql.connector.Error as err:
        print(f"Eroare la actualizare: {err}")
        db.rollback()


def delete_record(table_name, record_id):
    cursor = db.cursor(dictionary=True)

    print(f"\n*** Stergere inregistrare din tabela {table_name} ***")

    delete_query = f"DELETE FROM {table_name} WHERE ID_{table_name} = {record_id}"

    try:
        cursor.execute(delete_query)
        db.commit()
        print("inregistrare stearsa cu succes.")
    except mysql.connector.Error as err:
        print(f"Eroare la stergere: {err}")
        db.rollback()


# punctul c) - cerere complexa
def complex_query():
    cursor = db.cursor(dictionary=True)

    print("\n*** Afisare rezultatul unei cereri complexe ***")

    query = """
        SELECT 
            a.ID_Abonamente,
            a.TipAbonament,
            a.Tip_persoana_acordat,
            a.Durata,
            a.Pret,
            l.NumarLinie,
            l.Traseu,
            c.Nume AS NumeClient,
            c.Prenume AS PrenumeClient,
            c.AdresaEmail
        FROM 
            Abonamente a
        JOIN 
            Clienti c ON a.ClientID = c.ID_Clienti
        JOIN 
            Abonamente_Linii al ON a.ID_Abonamente = al.AbonamentID_Abonamente_Linii
        JOIN 
            LiniiAutovehicule l ON al.LiniiAutovehiculID = l.ID_LiniiAutovehicule
        WHERE 
            a.TipAbonament = 'Abonament lunar'
            AND a.Durata >= 30
            AND l.OraPlecare >= '08:00:00';
    """
    try:
        cursor.execute(query)
        result = cursor.fetchall()

        # Afisarea datelor cu PrettyTable
        if result:
            table = PrettyTable(result[0].keys())
            for row in result:
                table.add_row(row.values())
            print(table)
        else:
            print("Nu exista rezultate pentru cererea data.")
    except mysql.connector.Error as err:
        print(f"Eroare la executarea cererii complexe: {err}")


# punctul d) - cerere cu functii de grupare si clauza HAVING
def query_using_group_by_having():
    cursor = db.cursor(dictionary=True)

    print("\n*** Afisare rezultatul unei cereri cu functii de grupare si clauza HAVING ***")

    query = """
        SELECT 
            TipAbonament,
            COUNT(*) AS NumarTotalAbonamente
        FROM 
            Abonamente
        GROUP BY 
            TipAbonament
        HAVING 
            NumarTotalAbonamente > 2;
    """
    try:
        cursor.execute(query)
        result = cursor.fetchall()

        # Afisare rezultate
        if result:
            header = result[0].keys()
            print("\t".join(header))

            for row in result:
                print("\t".join(str(value) for value in row.values()))
        else:
            print("Nu exista rezultate pentru cererea data.")
    except mysql.connector.Error as err:
        print(f"Eroare la executarea cererii complexe: {err}")


def on_delete_cascade(cursor, db):
    print("\n*** Stergere in cascada ***")

    # Obtine numele tabelului de la utilizator
    table_name = input("Introduceti numele tabelului: ")

    # Obtine ID-ul înregistrării de la utilizator
    record_id_to_delete = input(f"Introduceti ID-ul inregistrarii din tabelul {table_name} care va fi stearsa: ")

    try:
        # Sterge înregistrarea si utilizează constrangerea ON DELETE CASCADE
        cursor.execute(f"DELETE FROM {table_name} WHERE ID_{table_name} = {record_id_to_delete}")
        db.commit()
        print(
            f"Inregistrarea cu ID-ul {record_id_to_delete} din tabela {table_name} si inregistrarile asociate au fost sterse cu succes.")
    except mysql.connector.Error as err:
        print(f"Eroare la stergerea inregistrarii: {err}")
        db.rollback()


def main():
    cursor = db.cursor(dictionary=True)
    while True:
        print("\n=== MENIU ===")
        print("1. Listare continut tabele")
        print("2. Modificare / stergere inregistrare")
        print("3. Afisare rezultat cerere complexa")
        print("4. Afisare rezultat cerere cu functii grup si clauza HAVING")
        print("5. Implementare constrangere ON DELETE CASCADE si exemplificare")
        print("0. Iesire")

        choice = input("Alegeti optiunea: ")

        if choice == "1":
            list_all_tables()
        elif choice == "2":
            table_name = input("Introduceti numele tabelului pentru editare/stergere: ")
            edit_or_delete = input("Alegeti optiunea (editare/stergere): ")

            if edit_or_delete.lower() == "editare":
                record_id = input("Introduceti ID-ul inregistrarii pentru editare: ")
                edit_record(table_name, record_id)
            elif edit_or_delete.lower() == "stergere":
                record_id = input("Introduceti ID-ul inregistrarii pentru stergere: ")
                delete_record(table_name, record_id)
            else:
                print("Optiune invalida.")
        elif choice == "3":
            complex_query()
        elif choice == "4":
            query_using_group_by_having()
        elif choice == "5":
            on_delete_cascade(cursor, db)

        elif choice == "0":
            print("La revedere!")
            break
        else:
            print("Optiune invalida. Incercati din nou.")


if __name__ == "__main__":
    main()
