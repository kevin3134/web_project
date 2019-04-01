from django.shortcuts import render, get_object_or_404
from django.core import serializers
from django.http import HttpResponse, Http404
from django.utils import timezone
import json
from django.views.decorators.csrf import ensure_csrf_cookie

# Imports the Item class
from time_management.models import *


#@ensure_csrf_cookie
def home(request):
    return render(request, 'time_management/action_record.html', {})

def add_item(request):
    if request.method != 'POST':
        raise Http404

    if not 'item' in request.POST or not request.POST['item']:
        message = 'You must enter an item to add.'
        json_error = '{ "error": "'+message+'" }'
        return HttpResponse(json_error, content_type='application/json')

    jsondata = json.loads(request.POST['item'])
    #print(type(jsondata['create_time']))

    new_item = Item(process_name=jsondata['process_name'],
                    ip_addr=request.META['REMOTE_ADDR'],
                    update_time=jsondata['update_time'],
                    create_time=jsondata['create_time'],
                    type=jsondata['type'],
                    username=jsondata['username'])
    new_item.save()

    response_text = serializers.serialize('json', Item.objects.all())
    return HttpResponse(response_text, content_type='application/json')

    
def delete_item(request, item_id):
    if request.method != 'POST':
        raise Http404

    item = get_object_or_404(Item, id=item_id)
    item.delete()

    response_text = serializers.serialize('json', Item.objects.all())
    return HttpResponse(response_text, content_type='application/json')


def get_list_json(request):
    response_text = serializers.serialize('json', Item.objects.all())
    return HttpResponse(response_text, content_type='application/json')


def get_list_xml(request):
    response_text = serializers.serialize('xml', Item.objects.all())
    return HttpResponse(response_text, content_type='application/xml')


def get_list_xml_template(request):
    context = { 'items': Item.objects.all() }
    return render(request, 'time_management/items.xml', context, content_type='application/xml')
