from django.db import models

# Data model for a todo-list item
class Item(models.Model):
    process_name = models.CharField(max_length=200)
    ip_addr = models.GenericIPAddressField()
    update_time = models.DateTimeField()
    create_time = models.DateTimeField()
    type = models.CharField(max_length=50)
    username = models.CharField(max_length=50)

    def __unicode__(self):
        return self.text
