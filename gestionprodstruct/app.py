# Import packages
from dash import Dash, html, dash_table, dcc, callback, Output, Input, State, ctx
from datetime import date, timedelta
from dateutil.relativedelta import relativedelta
import pandas as pd
import plotly.express as px
import plotly.graph_objs as go
import dash_bootstrap_components as dbc
from Application.GetSpots import get_spots
# from Application.GetPriceAndDeltas import get_price, get_deltas

# Initialize the app - incorporate a Dash Bootstrap theme
external_stylesheets = [dbc.themes.LUX]
app = Dash(__name__, external_stylesheets=external_stylesheets, suppress_callback_exceptions=False)

# Create the variables we will use
data = {
    'Action': ['BOVESPA', 'DAX', 'TSX300'],
    'Quantité': [0,0,0],
    'Prix': [0,0,0]
}
df_pf = pd.DataFrame(data)
df_pf['Valeur'] = df_pf['Prix'] * df_pf['Quantité']

df_rebalancement = pd.DataFrame()

# Sample DataFrame
data = {
    'Portfolio Value': [10, 15, 20, 25],
    'Product Price': [5, 8, 12, 18]
}
history = pd.DataFrame(data, index=pd.date_range(start='2023-01-01', periods=4))

today = date(2008,11,8)

app.layout = dbc.Container([    
    # App title
    dbc.Row([
        html.Div('Application de gestion de produits structurés', className="text-primary text-center fs-1 py-4")
    ]),
        
    # Periods description
    dbc.Row([
        html.Div('Veuillez choisir la période de test. La première période de test se déroule du 5 Juillet 2000 au 5 Juillet 2005. La seconde période de test de déroule du 4 Janvier 2005 au 4 Janvier 2010. Et la dernière se déroule du 5 Janvier 2009 au 6 Janvier 2014.', className="text-primary text-center fs-4 py-4")
    ]),
    
    # Period selector
    dbc.Row([
        dbc.Col([
            dbc.Button('Période 1', id="period-1")
        ], width=2),
        dbc.Col([
            dbc.Button('Période 2', id="period-2")
        ], width=2),
        dbc.Col([
            dbc.Button('Période 3', id="period-3")
        ], width=2),
    ], class_name="py-4", justify="center"),
], id="container", fluid=True)

@callback(
    Output('container', 'children'),
    Input('period-1', 'n_clicks'),
    Input('period-2', 'n_clicks'),
    Input('period-3', 'n_clicks'),
    prevent_initial_call=True
)
def render_content(p1, p2, p3):
    global today
    global monitoring_days
    if ctx.triggered_id=="period-1":
        today = date(2000,7,5)
        monitoring_days = [date(2001, 7, 3), date(2002, 7, 2), date(2003,7,2), date(2004,7,2), date(2005,7,5)]
    elif ctx.triggered_id=="period-2":
        today = date(2005,1,4)
        monitoring_days = [date(2006,1,4), date(2007,1,4), date(2008,1,4), date(2009,1,5), date(2010,1,4)]
    else:
        today = date(2009,1,5)
        monitoring_days = [date(2010,1,4), date(2011,1,4), date(2012,1,4), date(2013,1,4), date(2014,1,6)]
    return appLayout

# App layout
appLayout = dbc.Container([
    dcc.Location(id="url", refresh=True),
    
    # App title
    dbc.Row([
        html.Div('Application de gestion de produits structurés', className="text-primary text-center fs-1 py-4")
    ]),
    
    # Date
    dbc.Row([
        html.Div(children=today, className="text-primary text-center fs-3 py-4", id="date")
    ]),
    
    # Scenario launcher
    dbc.Row([
        html.Div("Lancer un scénario", className="text-primary text-center fs-3 py-4")
    ]),
    
    dbc.Row([
        dbc.Col([
            html.Div("En rebalançant tous les:"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='days-simu', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("jours"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='months-simu', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("mois"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='years-simu', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("années"),
        ], width=1),
        dbc.Col([
            dbc.Button('Lancer', id="launch-simu") 
        ], width=2),
    ], class_name="py-4", justify="around"),
    
    # Date
    dbc.Row([
        html.Div("Avancer manuellement", className="text-primary text-center fs-3 py-4")
    ]),

    # Date forwarder
    dbc.Row([
        dbc.Col([
            html.Div("Avancer de:"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='days', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("jours"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='months', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("mois"),
        ], width=1),
        dbc.Col([
            dcc.Input(id='years', value=0, type='number'), 
        ], width=1),
        dbc.Col([
            html.Div("années"),
        ], width=1),
        dbc.Col([
            dbc.Button('Avancer', id="forward-date") 
        ], width=2),
    ], class_name="py-4", justify="around"),

    # Portfolio
    dbc.Row([
        dbc.Col([
            html.Div('Votre portefeuille: ', className="text-primary text-center fs-3 pb-4")
        ], width=2),

        dbc.Col([
            dash_table.DataTable(data=df_pf.to_dict('records'), page_size=10, id='pf-table')
        ], width=10),
    ]),

    # Actions
    dbc.Row([
        dbc.Col([
            dbc.Button('Mettre à jour les prix', id="update-prices")
        ], width=2),

        dbc.Col([
            dbc.Button('Rebalancer le portefeuille', id="update-pf")
        ], width=2),
    ], class_name="py-4", justify="center"),

    # Rebalancing
    dbc.Row(id="rebalancing", children=
    [
        dbc.Col([
            dash_table.DataTable(data=df_rebalancement.to_dict('records'), page_size=10, id='rebalancement-table')
        ], width=10),

        dbc.Col([
            dbc.Button('Passer ordre d\'achat', color="success", id="pass-order", className="py-2 my-2"),
            dbc.Button('Annuler l\'ordre', color="danger", id="cancel-order", className="py-2 my-2")
        ], width=2),
    ], class_name="py-4", align="center", justify="center", style={'display': 'none'}),

    # Price
    dbc.Row([
        dbc.Col([
            html.Div(id="prod-price", children='Prix du produit structuré: 10€', className="text-primary text-center fs-3 pb-4")
        ], width=3),
        dbc.Col([            
            dbc.Button('Mettre à jour le prix', id="update-price") 
        ], width=2),       
    ], class_name="py-4", justify="center"),

    # Graph
    dbc.Row([    
        dcc.Graph(
            id='graph',
            figure={
                'data': [
                    go.Scatter(
                        x=history.index,
                        y=history[column],
                        mode='lines',
                        name=column
                    ) for column in history.columns
                ],
                'layout': {
                    'title': 'PnL vs Product price',
                    'xaxis': {'title': 'Date'},
                    'yaxis': {'title': 'Valeur'}
                }
            }
        )
    ], class_name="py-4", justify="center"),
    
    # Reset
    dbc.Row([
        dbc.Col([            
            dbc.Button('Recommencer', id="reset") 
        ], width=2),
    ], class_name="py-4", justify="center"),

], fluid=True)

# Update porfolio values according to new assets prices or rebalance the pf
@callback(
    Output(component_id='pf-table', component_property='data', allow_duplicate=True),
    Output("graph", "figure", allow_duplicate=True),
    Input(component_id='days-simu', component_property='value'),
    Input(component_id='months-simu', component_property='value'),
    Input(component_id='years-simu', component_property='value'),
    Input(component_id='launch-simu', component_property='n_clicks'),
    State('pf-table', 'data'),
    State("graph", "figure"),
    prevent_initial_call=True
)
def simulate(days, months, years, launch, table, fig):
    global df_pf
    
    if ctx.triggered_id!="launch-simu":
        return table, fig
    
    global today
    global history
    today += timedelta(days=days) + relativedelta(months=months, years=years)
    while today < monitoring_days[-1]:
        df_market = get_spots(today)
        df_rebalancement = get_deltas(str(today), True)
        for index,row in df_pf.iterrows():
            df_pf.at[index, 'Prix'] = df_market.loc[row.Action]
            df_pf.at[index, 'Quantité'] = df_rebalancement.loc[row.Action]
            df_pf['Valeur'] = df_pf.Quantité * df_pf.Prix
        history.at[today, "Portfolio Value"] = df_pf.Valeur.sum()
        history.at[today, "Product Price"] = get_price(str(today))
        today += timedelta(days=days) + relativedelta(months=months, years=years)
        
    today = monitoring_days[-1]    
    df_market = get_spots(today)
    df_rebalancement = get_deltas(str(today), True)
    for index,row in df_pf.iterrows():
        df_pf.at[index, 'Prix'] = df_market.loc[row.Action]
        df_pf.at[index, 'Quantité'] = df_rebalancement.loc[row.Action]
        df_pf['Valeur'] = df_pf.Quantité * df_pf.Prix
    history.at[today, "Portfolio Value"] = df_pf.Valeur.sum()
    history.at[today, "Product Price"] = get_price(str(today))
        
    
    fig={
        'data': [
            go.Scatter(
                x=history.index,
                y=history[column],
                mode='lines',
                name=column
            ) for column in history.columns
        ],
        'layout': {
            'title': 'PnL vs Product price',
            'xaxis': {'title': 'Date'},
            'yaxis': {'title': 'Valeur'}
        }
    }

    return df_pf.to_dict('records'), fig


# Update porfolio values according to new assets prices or rebalance the pf
@callback(
    Output(component_id='pf-table', component_property='data', allow_duplicate=True),
    Output("graph", "figure", allow_duplicate=True),
    Input(component_id='update-prices', component_property='n_clicks'),
    Input(component_id='pass-order', component_property='n_clicks'),prevent_initial_call=True
)
def update_pf(update, rebalance):
    global df_pf
    
    if ctx.triggered_id=="pass-order":
        df_pf = df_rebalancement
        
    df_market = get_spots(today)
    
    for index,row in df_pf.iterrows():
        df_pf.at[index, 'Prix'] = df_market.loc[row.Action]
        df_pf['Valeur'] = df_pf.Quantité * df_pf.Prix
        
    
    global history
    history.at[today, "Portfolio Value"] = df_pf.Valeur.sum()
    fig={
        'data': [
            go.Scatter(
                x=history.index,
                y=history[column],
                mode='lines',
                name=column
            ) for column in history.columns
        ],
        'layout': {
            'title': 'PnL vs Product price',
            'xaxis': {'title': 'Date'},
            'yaxis': {'title': 'Valeur'}
        }
    }

    return df_pf.to_dict('records'), fig


# Update porfolio values according to new assets prices and render the buttons so the trader can pass or cancel the orders
@callback(
    Output(component_id='rebalancing', component_property='style'),
    Output(component_id='rebalancement-table', component_property='data'),
    Input(component_id='update-pf', component_property='n_clicks'),
    Input(component_id='cancel-order', component_property='n_clicks'),
    Input(component_id='pass-order', component_property='n_clicks'),
    prevent_initial_call=True
)
def compute_rebalancing(rebalance, cancel, order):
    global df_rebalancement
    
    #TODO handle si pas possible de rebalancer à cette date
    
    if ctx.triggered_id=="cancel-order" or ctx.triggered_id=="pass-order":
        return {'display': 'none'}, df_rebalancement.to_dict('records')
    
    if rebalance is None:
        style = {'display': 'none'}
    else:
        style = {'display': 'flex'}
    
    data = {
        'Action': ['AAPL', 'GOOGL', 'TSLA', 'AMZN'],
        'Quantité': [42, 69, 42, 69]
    }
    df_rebalancement = get_deltas(str(today), today in monitoring_days)

    return style, df_rebalancement.to_dict('records')


# Update the product price
@callback(
    Output("prod-price", "children"),
    Output("graph", "figure", allow_duplicate=True),
    Input("update-price", "n_clicks"),
    prevent_initial_call=True
)
def update_product_price(n_clicks):
    price = get_price(str(today))
    
    global history
    history.at[today, "Product Price"] = price
    fig={
        'data': [
            go.Scatter(
                x=history.index,
                y=history[column],
                mode='lines',
                name=column
            ) for column in history.columns
        ],
        'layout': {
            'title': 'PnL vs Product price',
            'xaxis': {'title': 'Date'},
            'yaxis': {'title': 'Valeur'}
        }
    }
    return f"Prix du produit structuré: {price}€", fig


# Forward the date
@callback(
    Output("date", "children"),
    Input("forward-date", "n_clicks"),
    Input("days", "value"),
    Input("months", "value"),
    Input("years", "value"),
    prevent_initial_call=False
)
def forward_date(n_clicks, days, months, years):
    global today
    if ctx.triggered_id=="period-1":
        today = date(2000,7,5)
    elif ctx.triggered_id=="period-2":
        today = date(2005,1,4)
    elif ctx.triggered_id=="period-3":
        today = date(2009,1,5)
    
    elif ctx.triggered_id=="forward-date":
        today += timedelta(days=days) + relativedelta(months=months, years=years)
        if today > monitoring_days[-1]:
            today = monitoring_days[-1]
    return today.strftime("%Y-%m-%d")

# Reset the page
@callback(
    Output("url", "href"),
    Input("reset", "n_clicks"),
    prevent_initial_call=True
)
def reset(n_clicks):
    return "/"

# Run the app
if __name__ == '__main__':
    app.run(debug=True)
