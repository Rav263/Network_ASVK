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
            'background-color': 'BFD7B5',
            'label': 'data(label)'
        }
    },
    {
        'selector': 'edge',
        'style': {
            'label': 'data(label)',
            'line-color': '#A3C4BC'
        }
    }
]

app.layout = html.Div([
    html.Div([
        html.Button('Add Node', id='btn-add-node', n_clicks_timestamp='0'),
        html.Button('Remove Node', id='btn-remove-node', n_clicks_timestamp='0'),
        html.Button('Calc path', id='btn-calc-path', n_clicks_timestamp='0'),
        html.Div(style={'width': '50%', 'display': 'inline'}, children=[
            'Edge weight:',
            dcc.Input(id='input-line-color', type='text')
        ]),
        html.Button('Applay edge weight', id='btn-submit', n_clicks_timestamp='0'),
        html.P(id='info'),
    ]),
    
    dcc.Dropdown(
        id='dropdown-update-layout',
        value='circle',
        clearable=False,
        options=[
            {'label': name.capitalize(), 'value': name}
            for name in ['circle', 'grid', 'random', 'cose', 'concentric']
        ]
    ),

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
edge_flag = 0
last_calc = '0'
last_submit = '0'
last_edge_weight = None

def send_data_to_server(edges, nodes):
    sock = socket.socket()
    sock.connect(('localhost', 19121))
    an_edges = []

    for an in edges:
        an_edges.append(an['data']['source'])
        an_edges.append(an['data']['target'])
        an_edges.append(an['data']['label'])

    print(an_edges)
    
    counter = 0
    for an in an_edges:
        counter += len(an) + 1

    print(counter)
    print(counter.to_bytes(4, byteorder='little'))
    sock.send(counter.to_bytes(4, byteorder='little'))


    for an in an_edges:
        sock.send(an.encode("utf-8"))
        sock.send(b' ')

    return sock
def recv_data_from_server(sock):
    path = []
    while True:
        data = sock.recv(1024)
        if not data:
            break
        path.append(data)

    sock.close()

    return data



@app.callback(Output('info', 'children'),
            [Input('btn-calc-path', 'n_clicks_timestamp')],
            [State('cytoscape-elements', 'elements')])
def cacl_path(btn_calc, elements):
    global last_calc
    if int(btn_calc) == int(last_calc):
        return ""

    sock = send_data_to_server(edges, nodes)

    path = recv_data_from_server(sock)

    return path

@app.callback(Output('cytoscape-elements', 'layout'),
              [Input('dropdown-update-layout', 'value')])
def update_layout(layout):
    return {
        'name': layout,
        'rows': 3,
        'animate': True
    }


@app.callback(Output('cytoscape-elements', 'elements'),
              [Input('cytoscape-elements', 'tapNodeData'),
               Input('btn-submit', 'n_clicks_timestamp'),
               Input('btn-add-node', 'n_clicks_timestamp'),
               Input('btn-remove-node', 'n_clicks_timestamp'),
               #Input('btn-calc-path', 'n_clicks_timestamp')
               ],
              [State('cytoscape-elements', 'elements'), 
                State('input-line-color', 'value'),
                State('info', 'children')])
def update_elements(data, btn_submit, btn_add, btn_remove, elements, edge_weight, field):
    global flag
    global last_node
    global lat
    global long
    global node_num
    global last_add
    global last_remove
    #global last_calc
    global last_submit
    global edge_flag

    if edge_flag == 1:
        if int(btn_submit) != int(last_submit) and edge_weight != None:
            edges[-1]['data']['label'] = edge_weight
            edge_flag = 0
            last_submit = btn_submit
        return edges+nodes

    if data == last_node:
        if int(btn_add) != int(last_add):
            nodes.append({
                'data': {'id': node_num, 'label': node_num}, 
                'position': {'x': 20, 'y': 20},
            });
            node_num += 1
            last_add = btn_add
            return edges+nodes
        elif int(btn_remove) != int(last_remove):
            last_remove = btn_remove
            del nodes[-1]
            return edges+nodes
      #  elif int(btn_calc) != int(last_calc):
     #       send_data_to_socket(edges, nodes)
      #      return edges+nodes

    else:
        if flag == 1:
            flag = 0
            edges.append({
                'data': {'source': last_node['id'], 'target': data['id'], 'label': "Please enter edge weight"},
            })
            field = "Please enter edge weight"
            edge_flag = 1
            last_node = data
            return edges+nodes
        else:
            #nodes['data'][data['id']]
            flag = 1
            last_node = data
    return elements

if __name__ == '__main__':
    app.run_server(debug=True)

