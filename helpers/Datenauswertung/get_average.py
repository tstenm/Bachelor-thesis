import csv

def durchschnitt_load_store_minor(dateiname):
    sum_load = 0
    sum_store = 0
    sum_minor = 0
    count = 0

    with open(dateiname, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            sum_load += int(row['dTLB-load-misses'])
            sum_store += int(row['dTLB-store-misses'])
            sum_minor += int(row['minor-faults'])
            count += 1

    durchschnitt_load = sum_load / count if count > 0 else 0
    durchschnitt_store = sum_store / count if count > 0 else 0
    durchschnitt_minor = sum_minor / count if count > 0 else 0

    return durchschnitt_load, durchschnitt_store, durchschnitt_minor

#Dateiname nach Bedarf anpassen, Verzeichnsisstruktur beachten
dateiname = ''  
avg_load, avg_store, avg_minor = durchschnitt_load_store_minor(dateiname)
print(f'Durchschnitt dTLB-load-misses: {avg_load:.2f}')
print(f'Durchschnitt dTLB-store-misses: {avg_store:.2f}')
print(f'Durchschnitt minor-faults: {avg_minor:.2f}')

