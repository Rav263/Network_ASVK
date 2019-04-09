import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_cytoscape as cyto
import socket


from pprint import pprint
from dash.dependencies import Input, Output, State


app = dash.Dash(__name__)



edges = []
nodes = []

lat = 0
long = 0
node_num = 0



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
        html.Button('Remove Node', id='btn-remove-node', n_clicks_timestamp='0'),
        html.Button('Calc path', id='btn-calc-path', n_clicks_timestamp='0')
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
last_node = None
last_add = '0'
last_remove = '0'


def send_data_to_socket(edges, nodes):
   sock = socket.socket()
   sock.connect(('localhost', 2222))

   sock.close()



@app.callback(Output('cytoscape-elements', 'elements'),
              [Input('cytoscape-elements', 'tapNodeData'),
               Input('btn-add-node', 'n_clicks_timestamp'),
               Input('btn-remove-node', 'n_clicks_timestamp'),
               Input('btn-calc-path', 'n_clicks_timestamp')],
              [State('cytoscape-elements', 'elements')])
def update_elements(data, btn_add, btn_remove, btn_calc, elements):
    global flag
    global last_node
    global lat
    global long
    global node_num
    global last_add
    global last_remove
    
    print(nodes)

    if data == last_node:
        if int(btn_add) != int(last_add):
            nodes.append({
                'data': {'id': node_num, 'label': node_num}, 
                'position': {'x': 20, 'y': 20}
            });
            node_num += 1
            last_add = btn_add
            return edges+nodes
        elif int(btn_remove) != int(last_remove):
            last_remove = btn_remove
            del nodes[-1]
            return edges+nodes
    else:
        if flag == 1:
            flag = 0
            edges.append({'data': {'source': last_node['id'], 'target': data['id']}})
            last_node = data
            return edges+nodes
        else:
            #nodes['data'][data['id']]
            flag = 1
            last_node = data
    return elements

if __name__ == '__main__':
    app.run_server(debug=True)

