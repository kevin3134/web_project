from django.urls import path
from time_management import views

urlpatterns =[
    path('', views.home),
    path('add-item', views.add_item),
    path('delete-item/<int:item_id>', views.delete_item),
    path('get-list-json', views.get_list_json),
    path('get-list-xml', views.get_list_xml),
    path('get-list-xml-template', views.get_list_xml_template),
]
