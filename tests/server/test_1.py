import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_cytoscape as cyto

from pprint import pprint
from dash.dependencies import Input, Output, State


app = dash.Dash(__name__)



edges = [
  #  {'data': {'source': source, 'targer': target}}
]

lat = 0
long = 0
node_num = 0


nodes = [
]

default_stylesheet = [
    {
        'selector': 'node',
        'style': {
            'background-color': '#BFD7B5',
            'label': 'data(label)'
        }
    },
    {
        'selector': 'edge',
        'style': {
            'line-color': '#A3C4BC'
        }
    }
]

app.layout = html.Div([
    html.Div([
        html.Button('Add Node', id='btn-add-node', n_clicks_timestamp='0'),
        html.Button('Remove Node', id='btn-remove-node', n_clicks_timestamp='0')
    ]),

    cyto.Cytoscape(
        id='cytoscape-elements', 
        layout={'name': 'circle'}, 
        stylesheet=default_stylesheet,
        style={'width': '100%', 'height': '450px'},
        elements=edges+nodes
    ),
])

flag = 0
last_node = 0





@app.callback(Output('cytoscape-elements', 'elements'),
              [Input('cytoscape-elements', 'tapNodeData'),
               Input('btn-add-node', 'n_clicks_timestamp'),
               Input('btn-remove-node', 'n_clicks_timestamp')],
              [State('cytoscape-elements', 'elements')])

def update_elements(data, btn_add, btn_remove, elements):
    global flag
    global last_node
    global lat
    global long
    global node_num

    print(data)
    print(btn_add)
    print(btn_remove)

    if flag:
        flag = 0
        edges.append({'data': {'source': last_node['id'], 'target': data['id']}})
        return  edges+nodes 
    flag = 1
    last_node = data
    print(last_node)
    if int(btn_add) > int(btn_remove):
        nodes.append({
            'data': {'id': node_num, 'label': node_num}, 
            'position': {'x': 20 * lat, 'y': 20 * long}
        });
        lat += 1
        long += 1
        node_num += 1
    
        return nodes+edges
    return elements    

if __name__ == '__main__':
    app.run_server(debug=True)

