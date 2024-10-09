from datetime import datetime
import grpc
from GrpcPricer_pb2 import PricingInput
from GrpcPricer_pb2_grpc import GrpcPricerStub
import GrpcPricer_pb2_grpc
import pandas as pd
import numpy as np
class OutputData:
    def __init__(self, value: float, date: datetime, deltas: list, deltas_std_dev: list, price: float, price_std_dev: float):
        self.value = value
        self.date = date
        self.deltas = deltas
        self.deltas_std_dev = deltas_std_dev
        self.price = price
        self.price_std_dev = price_std_dev


def generate_outputdata(date: datetime, val: float, pricing_input: PricingInput, client: GrpcPricerStub) -> OutputData:
        pricing_results = client.PriceAndDeltas(pricing_input)
        output_data = OutputData(
            value=val,
            date=date,
            deltas=list(pricing_results.deltas),
            deltas_std_dev=list(pricing_results.deltasStdDev),
            price=pricing_results.price,
            price_std_dev=pricing_results.priceStdDev
        )
        print(output_data.price)
        print(output_data.deltas)
        return output_data


#starting_date = T0
def createInput(starting_date, date):

    prices_df = pd.read_excel("../Data/DonneesGPS2024.xlsx", sheet_name="ClosePrice")[["Date", "DAX", "BOVESPA", "TSX300"]]
    taux_change_prices_df = pd.read_excel("../Data/DonneesGPS2024.xlsx", sheet_name="XFORPrice")[["Date", "XBRL", "XCAD"]]

    starting_date = datetime.strptime(starting_date, "%d/%m/%Y")
    date = datetime.strptime(date, "%d/%m/%Y")

    prices_df = prices_df.merge(taux_change_prices_df, on="Date", how="inner")

    if prices_df[['DAX', 'BOVESPA', 'TSX300', 'XBRl', 'XCAD']].isna().any():
        filtered_prices_df = prices_df[prices_df['Date'] == date]
        prices_array = []
        prices_array.extend(filtered_prices_df[['DAX', 'BOVESPA', 'TSX300', 'XBRL', 'XCAD']].values[0])
    else:
        print("pas de données dispo")

    pricing_input = PricingInput()
    past_lines = pricing_input.past.add()
    past_lines.value.extend(prices_array)

    pricing_input.time = int(np.busday_count(starting_date.date(), date.date))
    pricing_input.monitoringDateReached = False

    return pricing_input






##################################################
#######################TEST#######################
##################################################


# Création d'un objet PricingInput
pricing_input = PricingInput()

# Ajout de lignes passées
past_lines1 = pricing_input.past.add()
past_lines1.value.extend([6961.73, 17134.93, 10323.75, 0.582368513710527, 0.704787146881377])



# Définition de monitoringDateReached
pricing_input.monitoringDateReached = True  # si False index out of range

# Définition de time
pricing_input.time = 0 # Remplacez par la valeur souhaitée
pricing_input.jsonFile = "/home/gagar/gestionprodstruct/Pricer/testProduct_0.json"
# Affichage de l'objet PricingInput
print(pricing_input)


with grpc.insecure_channel("localhost:50051") as channel:
    pricer = GrpcPricer_pb2_grpc.GrpcPricerStub(channel)
    generate_outputdata(0, 0, pricing_input, pricer)

